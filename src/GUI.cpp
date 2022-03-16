// * Do mình lười tách ra cho dễ nhìn
// * Nhưng mà làm gắn luôn thế này quan sát cũng tiện :))

#include <iostream>
#include <vector>
#include <string>
#include "Wave.cpp"

using std::cin;
using std::cout;
using std::string;
using std::endl;

std::vector<Wave> waves(4);

namespace GUI{
    // * Edit 1 file âm thanh
    // * @param wav File âm thanh cần chỉnh sửa
    void configureWave(Wave &wav);

    // * Màn hình menu chính
    void mainMenu();

    // * Màn hình hiển thị thông tin Wave
    void getWaveInfo(const Wave &wav);

    // * Thay đổi file nguồn
    void changeSourceFile(Wave &wav);
    
    // * Thay đổi Tần số mẫu
    void changeSampleRate(Wave &wav);

    // * Thay đổi số lượng kênh MONO | STEREO
    void changeNumChannel(Wave &wav);

    // * Đảo ngược tín hiệu mẫu
    void c_reverseSamples(Wave &wav);

    // * Nhân tín hiệu với một hằng số
    void c_MulSamplesWithConst(Wave &wav);

    // * Tạo hiệu ứng echo
    void c_echoSamples(Wave &wav);

    // * Nghe
    void listenWave(Wave &wav);

    void mainMenu(){
        int choose;
        // * Vòng lặp chương trình chính
        while (1) {
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v 1.0\n");
            printf("\n");
            printf("\n");
            printf("\t||==============================================================||\n");
            printf("\t||                                                              ||\n");
            printf("\t||     Muc do tieu ton bo nho %15d byte(s).          ||\n", waves.size() * sizeof(Wave));
            printf("\t||                                                              ||\n");
            printf("\t||==============================================================||\n");
            printf("\t||==========================**||MENU||**========================||\n");
            printf("\t||==============================================================||\n");
            printf("\t||                                                              ||\n");
            printf("\t||     1. Dieu chinh tin hieu am thanh thu nhat.                ||\n");
            printf("\t||     2. Dieu chinh tin hieu am thanh thu hai.                 ||\n");
            printf("\t||     3. Dieu chinh tin hieu am thanh thu ba.                  ||\n");
            printf("\t||     4. Xem thong tin cua toan bo cac hieu ung am thanh       ||\n");
            printf("\t||     0. Thoat chuong trinh.                                   ||\n");
            printf("\t||                                                              ||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\t||\tLua chon cua ban: ");
            cin >> choose;
            switch (choose)
            {
            case 1:
                configureWave(waves[1]);
                break;
            case 2:
                configureWave(waves[2]);
                break;
            case 3:
                configureWave(waves[3]);
                break;
            default:
                // TODO Ghi tên thành viên nhóm
                printf("\tThanh vien nhom:\n");
                printf("\tCam on ban da su dung phan mem dieu chinh am thanh cua nhom minh!\n");
                sleep(3);
                return;
                break;
            }
        }
    }


    void configureWave(Wave &wav) {
        int choose;
        // * Vòng lặp cho chức năng chỉnh sửa âm thanh
        // * Do 1 lần người ta muốn thực hiện nhiều chỉnh sửa
        // * Vậy nên mình sẽ để trong vòng lặp
        // * Chứ không thực hiện 1 lần rồi thôi
        // TODO: Echo
        // TODO: Delay
        // TODO: Nhân với 1 hằng số
        // TODO: Đảo tín hiệu
        // TODO: Cộng hai tin hiệu
        // TODO: Nhân hai tín hiệu
        // TODO: Tích chập
        // TODO: Tương quan chéo
        while(1) {
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            getWaveInfo(wav);
            printf("\t||==========================**||MENU||**========================||\n");
            printf("\t||==============================================================||\n");
            printf("\t||                                                              ||\n");
            printf("\t||    1.  Thay doi file nguon.                                  ||\n");   // * DONE
            printf("\t||    2.  Thay doi Tan so mau.                                  ||\n");   // * DONE
            printf("\t||    3.  Thay doi che do kenh MONO | STEREO.                   ||\n");   // * DONE
            printf("\t||    4.  Dao nguoc tin hieu mau.                               ||\n");   // * DONE
            printf("\t||    5.  Nhan tin hieu voi 1 hang so                           ||\n");   // * DONE
            printf("\t||        Luu y: - Chi nen nhan so thuoc khoang (-1, 1).        ||\n");
            printf("\t||               - May ban ra di thi dung hoi tai sao :)        ||\n");
            printf("\t||    6.  Tao hieu ung Echo.                                    ||\n");   // * DONE
            printf("\t||    7.  Tao hieu ung Delay.                                   ||\n");
            printf("\t||    8.  Cong hai tin hieu.                                    ||\n");
            printf("\t||    9.  Nhan hai tin hieu.                                    ||\n");
            printf("\t||   10.  Tich chap.                                            ||\n");
            printf("\t||   12.  Tuong quan cheo.                                      ||\n");
            printf("\t||   13.  Nghe file Am thanh cua tin hieu.                      ||\n");   // * DONE
            printf("\t||    0.  Quay tro lai.                                         ||\n");
            printf("\t||                                                              ||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\t||\tLua chon: ");
            cin >> choose;
            switch (choose) {
                case 0:
                    return;
                    break;
                case 1:
                    changeSourceFile(wav);
                    break;
                case 2:
                    changeSampleRate(wav);
                    break;
                case 3:
                    changeNumChannel(wav);
                    break;
                case 4:
                    c_reverseSamples(wav);
                    break;
                case 13:
                    listenWave(wav);
                    break;
                default:
                    printf("||\tKhong co chuc nang nay!\n");
                    break;
            }




        }
    }

    void getWaveInfo(const Wave &wav) {
            printf("\t||==============================================================||\n");
            printf("\t||                                                              ||\n");
            printf("\t||    Ten source file: %30s           ||\n", wav.getSource().c_str());
            printf("\t||    So mau:          %15ld                          ||\n", wav.getSampleCount());
            printf("\t||    Tan so lay mau:  %15d                          ||\n", wav.getSampleRate());
            printf("\t||    Thoi luong chay: %15.2f (s)                      ||\n", wav.getDurationAsSeconds());
            printf("\t||                                                              ||\n");
            printf("\t||==============================================================||\n");
    }

    void changeSourceFile(Wave &wav) {
        std::string fileName;
        bool check = true;
        while(check) {
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            printf("\t||==============================================================||\n");
            printf("\t||==================**||CHANGE SOURCE FILE||**==================||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\n\tChuong trinh chi ho tro file .wav va file .txt trong truong hop file txt chi la mang cac mau.");
            printf("\n\tNeu ban khong dung dinh dang txt, neu chuong trinh chay loi dan den hong hoc,");
            printf("\n\tChung toi khong chiu trach nhiem!\n");
            printf("\n");
            printf("\t||    Nhap ten file: ");
            cin >> fileName;
            if(fileName.substr(fileName.length() - 4) == ".txt" ||
               fileName.substr(fileName.length() - 4) == ".wav") {
                try {
                    wav.loadFromFile(fileName);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
                system("pause");
                check = false;
            } else {
                char c;
                printf("\n\tChuong trinh chi ho tro dinh dang txt va wav!\n");
                printf("\nBan co muon nhap lai (Y/y = YES | N/n (other) = NO):");
                cin >> c;
                if(c == 'Y' || c == 'y') {
                    check = true;
                } else {
                    check = false;
                }
            }
        }
    }

    void changeSampleRate(Wave &wav) {
        int value;
        system("cls");
        printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
        printf("\n");
        printf("\t||==================**||CHANGE SAMPLE RATE||**==================||\n");
        printf("\t||==============================================================||\n");
        printf("\n");
        printf("\t||    Nhap tan so: ");
        cin >> value;
        wav.setSampleRate(value);
        printf("\n\t||    Tan so lay mau hien tai: %8d Hz.\n", wav.getSampleRate());
        system("pause");
        return;
    }

    void changeNumChannel(Wave &wav) {
        int value;
        bool check = true;
        char c;
        while(check) {
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            printf("\t||=================**||CHANGE NUMBER CHANNEL||**================||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\n\tMONO = 1 | STEREO = 2");
            printf("\t||    Nhap so: ");
            cin >> value;
            if(value > 2 || value < 1) {
                printf("\n\tKhong ho tro nay loai, Xin loi!\n");
                printf("\n\tBan co muon nhap lai khong ? (Y/y = YES | N/n (other) = NO): ");
                cin >> c;
                if(c == 'Y' || c == 'y') {
                    check = true;
                } else {
                    check = false;
                }
            } else {
                wav.setSampleRate(value);
                printf("\n\t||    So luong kenh hien tai: %1d kenh.\n", wav.getChannel());
                sleep(2);
            }
        }
    }

    void listenWave(Wave &wav) {
        bool check = true;
        char c;
        while (check) {
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            getWaveInfo(wav);
            printf("\tPlaying ...\n");
            wav.play();
            printf("\tDa ket thuc!\n");
            printf("\tBan co muon nghe tiep khong? (Y/y = YES | N/n (other) = NO):");
            cin >> c;
            if (c == 'Y' || c == 'y') {
                check = true;
            } else {
                check = false;
            }
        }
    }

    void c_reverseSamples(Wave &wav) {
        system("cls");
        printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
        printf("\n");
        printf("\t||==============================================================||\n");
        printf("\t||====================**||REVERSE SAMPLES||**===================||\n");
        printf("\t||==============================================================||\n");
        printf("\n");
        printf("\t||\tDang xu li ...\n");
        wav.reverseWave();
        printf("\n\tDao nguoc tin hieu thanh cong!\n");
        system("pause");
    }

    void c_echoSamples(Wave &wav) {
        int n;
        bool check = true;
        char c;
        while(check){
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            printf("\t||==============================================================||\n");
            printf("\t||====================**||MAKE ECHO SOUND||**===================||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\n||\tBan muon tin hieu lap lai may lan (>1): ");
            cin >> n;
            if(n <= 0) {
                printf("\n\t||\tKhong hop le!\n\t||\tBan muon nhap lai khong ? (Y/y = YES | N/n (other) = NO): ");
                cin >> c;
                if (c == 'Y' || c == 'y') {
                    check = true;
                } else {
                    check = false;
                }
            } else if (n >= 5) {
                printf("\n\t||\tMay lag hoac bi lam sao thi minh khong biet dau!");
                printf("\n\t||\tBan co muon nhap lai gia tri khong hay tiep tuc voi gia tri n = %d?", n);
                printf("\n\t||\t(Y/y = YES | N/n (other) = NO): ");
                cin >> c;
                if (c != 'Y' && c != 'y') {
                    check = true;      
                    continue;
                }

            } else {
                continue;
            }
            printf("\t||\tDang xu li ...\n");
            wav = wav * n;
            printf("\t||\tXu li thanh cong!\n");
            system("pause");
        }
    }

    void c_MulSamplesWithConst(Wave &wav) {
        int n;
        bool check = true;
        char c;
        while(check){
            system("cls");
            printf("\tChuong trinh Dieu chinh Am thanh (Sound Equalizer Program) v1.0\n");
            printf("\n");
            printf("\t||==============================================================||\n");
            printf("\t||====================**||MAKE ECHO SOUND||**===================||\n");
            printf("\t||==============================================================||\n");
            printf("\n");
            printf("\n||\tBan muon tin hieu lap lai may lan (>1): ");
            cin >> n;
            if(n <= 0) {
                printf("\n\t||\tKhong hop le!\n\t||\tBan muon nhap lai khong ? (Y/y = YES | N/n (other) = NO): ");
                cin >> c;
                if (c == 'Y' || c == 'y') {
                    check = true;
                } else {
                    check = false;
                }
            } else if (n >= 5) {
                printf("\n\t||\tMay lag hoac bi lam sao thi minh khong biet dau!");
                printf("\n\t||\tBan co muon nhap lai gia tri khong hay tiep tuc voi gia tri n = %d?", n);
                printf("\n\t||\t(Y/y = YES | N/n (other) = NO): ");
                cin >> c;
                if (c == 'Y' || c == 'y') {
                    
                } else {
                    check = true;
                }
            }
            printf("\t||\tDang xu li ...\n");
        }
    }
}


