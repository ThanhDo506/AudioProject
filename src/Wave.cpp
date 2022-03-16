#include "common.h"

class Wave
{
  public:
    Wave() {
        _number_of_channels = 0;
        _sample_rate = 0;
        _file_name = "NULL";
    }

    // * Khởi tạo với file WAV hoặc TXT
    // * File khác sẽ báo lỗi
    // * @param fileName    tên file
    Wave(const std::string &fileName) { loadFromFile(fileName); }

    ~Wave() {}

    // * Phép cộng 2 tín hiệu | Trộn tín hiệu.
    // * @param other Obj Wave khác    
    // * @return new Wave
    Wave operator+(const Wave &other) {
        Wave wav = other;
        vector<sf::Int16> w1 = this->_samples, w2 = other._samples;
        if (w1.size() < w2.size()) {
            w1.resize(w2.size(), 0);
        } else {
            w2.resize(w1.size(), 0);
        }
        for (unsigned long long i = 0; i < w1.size(); i++) {
            w1[i] += w2[i];
        }
        wav._samples = w1;

        return wav;
    }

    // * Phép nhân tín hiệu với một hằng số.
    // * @param number    hằng
    // * @return new Wave
    Wave operator*(const double &number) {
        Wave wav = this->copy();
        for (unsigned long long i = 0; i < _samples.size(); i++) {
            wav._samples.at(i) *= number;
        }
        return wav;
    }

    // * Phép nhân hai tín hiệu.
    // * @param wave
    // * @return new Wave
    Wave operator*(const Wave &other) {
        Wave wav = other;
        // * Biến đổi sang dạng thập phân trong khoảng -1 -> 1
        vector<double> v_wav = Wave::toLow(this->_samples),
                       v_other = Wave::toLow(other._samples);
        if (v_wav.size() < v_other.size()) {
            v_wav.resize(v_other.size(), 0);
        } else {
            v_other.resize(v_wav.size(), 0);
        }
        for (unsigned long long i = 0; i < v_wav.size(); i++) {
            v_wav[i] *= v_other[i];
        }
        // * Biến đổi ngược trở lại thành dạng số nguyên
        // * Trong khoảng từ -32767 -> 32767 (tức trong khoảng +- 2^15 - 1)
        wav._samples = toHigh(v_wav);
        return wav;
    }

    Wave copy() {
        Wave wav;
        wav._samples = this->_samples;
        wav._number_of_channels = this->_number_of_channels;
        wav._sample_rate = this->_sample_rate;
        return wav;
    }

    // * Trả về một object Wave với Mẫu bị đảo ngược.
    // * @return new Wave
    Wave reverseWave() {
        Wave wav = this->copy();
        std::reverse(wav._samples.begin(), wav._samples.end());
        // wav._samples.reserve(wav._samples.size());
        return wav;
    }

    // * Tạo ra một echo Wave
    // * @param n   Số lần lặp
    // * @return  Wave
    Wave echoWave(const int &n) {
        Wave wav = this->copy();
        for (int i = 1; i < n; i++) {
            wav._samples.insert(wav._samples.end(), this->_samples.begin(),
                                this->_samples.end());
        }
        return wav;
    }

    // * Tạo ra một Wave bị delay.
    // * @param millisecond Số giây delay
    // * @return  new Wave
    Wave delayWave(const int &milliseconds) {
        Wave wav = this->copy();
        wav._samples.insert(wav._samples.begin(),
                            _sample_rate * 1.0f / 60 * milliseconds, 0);
        return wav;
    }

    // * Tích chập của Wave này với Wave other
    // * @param Wave    other
    // * @return Wave là tích chập
    Wave tichChap(const Wave &other) {
        Wave wav;
        vector<double> wav_t = Wave::toLow(this->_samples),
                       wav_o = Wave::toLow(other._samples);
        wav._samples.resize(wav_t.size() + wav_o.size() - 1, 0);
        vector<vector<double>> matrix(wav_t.size());
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].resize(wav_o.size(), 0);
            for (int j = 0; j < matrix[i].size(); j++) {
                matrix[i][j] = wav_t[i] * wav_o[j];
            }
        }
        for (unsigned long long k = 0; k < wav._samples.size(); k++) {
            for (int i = 0; i < wav_t.size(); i++) {
                for (int j = 0; j < wav_o.size(); j++) {
                    if (i + j - 1 == k) {
                        wav._samples[k] += matrix[i][j];
                    }
                }
            }
        }
        return wav;
    }

    // * Tương quan chéo giữa 2 Wave
    // * @param Wave    other
    // * @return Wave là tương quan chéo
    Wave tuongQuanCheo(const Wave &other) {
        Wave wav;
        vector<double> wav_t = Wave::toLow(this->_samples),
                       wav_o = Wave::toLow(other._samples);
        reverse(wav_t.begin(), wav_t.end());

        wav._samples.resize(wav_t.size() + wav_o.size() - 1, 0);

        vector<vector<double>> matrix(wav_t.size());

        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].resize(wav_o.size(), 0);
            for (int j = 0; j < matrix[i].size(); j++) {
                matrix[i][j] = wav_t[i] * wav_o[j];
            }
        }

        for (unsigned long long k = 0; k < wav._samples.size(); k++) {
            for (int i = 0; i < wav_t.size(); i++) {
                for (int j = 0; j < wav_o.size(); j++) {
                    if (i + j - 1 == k) {
                        wav._samples[k] += matrix[i][j];
                    }
                }
            }
        }
        return wav;
    }

    // * Đặt tần số lấy mẫu.
    // * @param Hz    Tần số.
    void setSampleRate(const int& Hz) {
        _sample_rate = Hz;
    }

    // * Đặt chế độ kênh.
    // * @param channel   Mono = 1 | Stereo = 2 | ETC
    void setChannel(const int &channel) {
        _number_of_channels = channel;
    }

    // * Nghe file wav.
    // * Mặc dù có thể load hẳn lại vào _soundBuffer
    // * Nhưng thư viện của SFML/Audio nó chạy không đúng
    // * Khiến file gốc âm thanh sau khi chuyển đổi nhiều lần
    // * Dẫn đến biến dạng tần số (cụ thể là tần số x2)
    // * Do cũng không cần tính toán trên _soundBuffer
    // * Vậy nên bây giờ _soundBuffer chỉ có nhiệm vụ là lấy thông tin
    // * từ file wav, không còn tác dụng nào khác
    void play() {
        sf::SoundBuffer sb;
        sb.loadFromSamples(&_samples[0], _samples.size(), 1, _sample_rate);
        sf::Sound sound;
        sound.setBuffer(sb);
        sound.play();
        sleep(getDurationAsSeconds());
        // system("pause");
    }

    // * @return Độ dài âm thanh file (second).
    float getDurationAsSeconds() const {
        if (_samples.empty()) {
            return 0;
        }
        return _samples.size() * 1.0f / _sample_rate;
    }

    // * Lấy số lượng kênh 1 = Mono | 2 = Stereo , etc
    // * @return Số lượng kênh
    sf::Int16 getChannel() const {
        return _number_of_channels;
    }

    // * @return Số lượng mẫu
    sf::Int64 getSampleCount() const {
        return _samples.size();
    }

    // * @return Mảng chứa mẫu
    std::vector<sf::Int16> getSamples() const {
        return _samples;
    }

    // * Tải dữ liệu từ file WAV, TXT vào obj
    // * Riêng file TXT chỉ chứa các biến số
    void loadFromFile(const string &fileName) {
        if (fileName.substr(fileName.size() - 4) == ".txt") {
            std::ifstream file(fileName);
            // Nếu không mở được file thì thông báo rồi kết thúc
            if (!file.is_open()) {
                throw std::runtime_error("Error opening file!");
            }
            double s;
            while (!file.eof()) {
                file >> s;
                _samples.push_back((sf::Int16)s);    
            }
            file.close();
            _number_of_channels = 2;
            _sample_rate = 44100;
        } else if (fileName.substr(fileName.size() - 4) == ".wav") {
            sf::SoundBuffer _soundBuffer;
            _soundBuffer.loadFromFile(fileName);
            loadBufferToChannels(_soundBuffer);
        } else {
            throw std::invalid_argument("Can read WAV and TXT file!");
        }
        _file_name = fileName;
    }
    
    // * @return Tên file WAV / TXT
    std::string getSource() const {
        return _file_name;
    }

    // * @return Tần số mẫu
    unsigned int getSampleRate() const {
        return _sample_rate;
    }

    void saveToFile(const string &fileName) const {
        sf::SoundBuffer sb;
        sb.loadFromSamples(&_samples[0], _samples.size(), _number_of_channels, _sample_rate);
        sb.saveToFile(fileName);
    }


private:
    // * Mảng chứa mẫu
    std::vector<sf::Int16> _samples;

    // * Tần số mẫu
    unsigned int _sample_rate;

    // * Số lượng kênh, thường là 2 | Stereo
    int _number_of_channels;

    // * Nguồn của file Wave
    std::string _file_name;

    // * Dùng để convert từ Mẫu -32767 -> 32767 
    // * thành Mẫu -1 -> 1
    // * @param _s  Mảng mẫu -32767 -> 32767
    // * @return Mảng mẫu -1 -> 1
    static vector<double> toLow(const vector<sf::Int16> &_s) {
        vector<double> res(_s.size());
        for (int i = 0; i < _s.size(); i++) {
            // res.push_back(_s[i] * 1.0f / 32767);
            res[i] = static_cast<double>(_s[i]) / 32767;
        }
        return res;
    }

    // * Dùng để convert từ Mẫu -1 -> 1 
    // * thành Mẫu -32767 -> 32767
    // * @param _s  Mảng mẫu -1 -> 1
    // * @return Mảng mẫu -32767 -> 32767
    static vector<sf::Int16> toHigh(const vector<double> &_s) {
        vector<sf::Int16> res(_s.size());
        for (int i = 0; i < _s.size(); i++) {
            res.push_back(_s[i] * 32767);
            res[i] = static_cast<sf::Int16>(_s[i] * 32767);
        }
        return res;
    }

    // * Tải giá trị mẫu từ _soundBuffer
    void loadBufferToChannels(sf::SoundBuffer &_soundBuffer) {
        const sf::Int16 * p_sb = _soundBuffer.getSamples();
        _samples.clear();
        for (sf::Int64 i = 0; i < _soundBuffer.getSampleCount(); i += 2) {
            _samples.push_back(p_sb[i]);
        }
        _number_of_channels = _soundBuffer.getChannelCount();
        _sample_rate = _soundBuffer.getSampleRate();
    }
};


