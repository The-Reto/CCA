#include <chrono>
#include <ratio>
#include "../../headers/CCA_RNG.h"
#include "../../headers/CCA_Hash.h"
#include "../../headers/CA_Board.h"
#include "../../headers/CCA_Board.h"
#include "../../headers/CCA_B_Enc.h"
#include "../../headers/CCA_S_Enc.h"
#include "../../headers/BitBoardFileWriter.h"
#include "../../headers/BitBoardFileReader.h"


void test_RNG() {
    using namespace std::chrono;

    static const int samples = 10'000'000;
    CCA_RNG test(35687634);
    
    std::cout << "Testing RNG Class by taking " << samples << " samples:\n";
    
    std::cout << "\tintegers: ";
    auto start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_int();
    }
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << "\tfloats: ";
    start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_float();
    }
    end = steady_clock::now();
    duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << "\tdoubles: ";
    start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_double();
    }
    end = steady_clock::now();
    duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << std::endl;
}

void test_Hash() {
    CCA_Hash txt_hasher, mp3_hasher, mp4_hasher;
    BitBoardFileReader txt_file("./test_data/test.txt"), mp3_file("./test_data/test.mp3"), mp4_file("./test_data/test.mp4");

    using namespace std::chrono;
    std::cout << "Testing Hash Class by taking the Hash of a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    txt_file.run(txt_hasher);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::nanoseconds durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ns/byte, "<< 512*durationMS.count() / 10'204.0 <<"ns/generation)\n";
    
    std::cout << "\tvideo file (" << 705'948'212 << " Bytes): ";
    start = steady_clock::now();
    mp4_file.run(mp4_hasher);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  705'948'212.0  << "ns/byte, "<< 512*durationMS.count()/  705'948'212.0  <<"ns/generation)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    mp3_file.run(mp3_hasher);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 41'508'864.0  << "ns/byte, "<< 512*durationMS.count() / 41'508'864.0 <<"ns/generation)\n";
    
    std::cout << std::endl;
}

void test_GOL() {
    using namespace std::chrono;
    Bit_Board<u_int64_t> board;

    for (int i = 0; i < 64; i++) {board[i] = 0;}
    // glider
    board[0] = 2;
    board[1] = 4;
    board[2] = 7;
    
    // blinker
    board[10]=3<<3;
    board[11]=3<<3;
    board[12]=3<<5;
    board[13]=3<<5;
    
    // rotator
    board[4] = 7<<24;
   
    // boat
    board[25] = 2<<3;
    board[24] = 40;
    board[23] = 16;
    board[22] = 32;
    
    CA_Board<u_int64_t, 64> test_GOL;
    test_GOL.set_board(board);
    const static int generations = 500000;
    std::cout << "Testing GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_GOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / generations << "ns/generation)\n";
    std::cout << std::endl;
    if (test_GOL.get(23,44)) {std::cout << "worjs" << std::endl;} //just to force the optimizer to actually run the code
}

void test_CGOL() {
    using namespace std::chrono;
    CCA_Board test_CGOL(0xefecafe1);
    const static int generations = 500000;
    std::cout << "Testing C-GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_CGOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / generations << "ns/generation)\n";
    
    std::cout << std::endl;
}

void test_B_Enc(){
    using namespace std::chrono;
    CCA_B_Enc encryptor_text("thisIs4T3st_text");
    CCA_B_Enc encryptor_video("thisIs4T3st_video");
    CCA_B_Enc encryptor_music("thisIs4T3st_music");
    
    std::cout << "Testing Block Encryption Class by encrypting a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    encryptor_text.encrypt("test_data/test.txt", "test_data/test-txt.trc");
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::nanoseconds durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ns/byte)\n";
    
    std::cout << "\tvideo file (" << 705'948'212 << " Bytes): ";
    start = steady_clock::now();
    encryptor_video.encrypt("test_data/test.mp4", "test_data/test-mp4.trc");
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  705'948'212.0  << "ns/byte)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    encryptor_music.encrypt("test_data/test.mp3", "test_data/test-mp3.trc");
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 41'508'864.0  << "ns/byte)\n";
    
    std::cout << std::endl;
} 

void test_B_Dec(){
    using namespace std::chrono;
    CCA_B_Enc encryptor_text("thisIs4T3st_text");
    CCA_B_Enc encryptor_video("thisIs4T3st_video");
    CCA_B_Enc encryptor_music("thisIs4T3st_music");
    
    std::cout << "Testing Block Encryption Class by decrypting a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    encryptor_text.decrypt("test_data/test-txt.trc", "test_data/test-DEC.txt");
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::nanoseconds durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ns/byte)\n";
    
    std::cout << "\tvideo file (" << 705'948'212 << " Bytes): ";
    start = steady_clock::now();
    encryptor_video.decrypt("test_data/test-mp4.trc", "test_data/test-DEC.mp4");
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  705'948'212.0  << "ns/byte)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    encryptor_music.decrypt("test_data/test-mp3.trc", "test_data/test-DEC.mp3");
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 41'508'864.0  << "ns/byte)\n";
    
    std::cout << std::endl;
} 

void test_S_Enc(){
    using namespace std::chrono;
    BitBoardFileWriter out_text("./test_data/test-txt.trc");
    BitBoardFileWriter out_video("./test_data/test-mp4.trc");
    BitBoardFileWriter out_music("./test_data/test-mp3.trc");
    CCA_S_Enc encryptor_text(out_text, "thisIs4T3st_text");
    CCA_S_Enc encryptor_video(out_video, "thisIs4T3st_video");
    CCA_S_Enc encryptor_music(out_music, "thisIs4T3st_music");
    BitBoardFileReader in_text("./test_data/test.txt");
    BitBoardFileReader in_video("./test_data/test.mp4");
    BitBoardFileReader in_music("./test_data/test.mp3");
    
    std::cout << "Testing Stream Encryption Class by encrypting a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    in_text.run(encryptor_text);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::nanoseconds durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ns/byte)\n";
    
    std::cout << "\tvideo file (" << 705'948'212 << " Bytes): ";
    start = steady_clock::now();
    in_video.run(encryptor_video);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  705'948'212.0  << "ns/byte)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    in_music.run(encryptor_music);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 41'508'864.0  << "ns/byte)\n";
    
    std::cout << std::endl;
} 


void test_S_Dec(){
    using namespace std::chrono;
    BitBoardFileWriter out_text("./test_data/test-dec.txt");
    BitBoardFileWriter out_video("./test_data/test-dec.mp4");
    BitBoardFileWriter out_music("./test_data/test-dec.mp3");
    CCA_S_Enc encryptor_text(out_text, "thisIs4T3st_text");
    CCA_S_Enc encryptor_video(out_video, "thisIs4T3st_video");
    CCA_S_Enc encryptor_music(out_music, "thisIs4T3st_music");
    BitBoardFileReader in_text("./test_data/test-txt.trc");
    BitBoardFileReader in_video("./test_data/test-mp4.trc");
    BitBoardFileReader in_music("./test_data/test-mp3.trc");
    
    std::cout << "Testing Stream Encryption Class by encrypting a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    in_text.run(encryptor_text);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::nanoseconds durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ns/byte)\n";
    
    std::cout << "\tvideo file (" << 705'948'212 << " Bytes): ";
    start = steady_clock::now();
    in_video.run(encryptor_video);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  705'948'212.0  << "ns/byte)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    in_music.run(encryptor_music);
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 41'508'864.0  << "ns/byte)\n";
    
    std::cout << std::endl;
} 


int main()
{
    //test_GOL();
    //test_CGOL();
    //test_RNG();
    test_Hash();
    //test_B_Enc();
    //test_B_Dec();
    test_S_Enc();
    test_S_Dec();
}