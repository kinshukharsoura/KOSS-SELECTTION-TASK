#include<bits/stdc++.h>
#include <conio.h>
using namespace std;
struct chip8{
    uint8_t V[16];
    uint16_t I;
    uint16_t PC;
    uint8_t SP;uint16_t stack[16];
    uint8_t memory[4096];
};
bool ROM(const char *p,uint8_t *m){
    ifstream file(p, ios::binary | ios::ate);
    if (!file.is_open()) {
        cout << "Sorry, idid not find thr file " << p << endl;
        return false;
    }
    streampos size = file.tellg();
    if (size > (4096-512)) {
        cout << "Sorry, the rom you entered is too large for CHIP 8" << endl;
        return false;
    }
    file.seekg(0, ios::beg);
    file.read((char*)&m[0x200], size);
    file.close();
    return true;
}
int main() {
    uint16_t pc=0x200;
    uint16_t i=0;
    uint8_t v[16] = {0};
    uint8_t m[4096];
    uint16_t s[16] = {0};
    uint8_t sp = 0;
    uint8_t display[64 * 32] = {0};

    // if (!ROM("ibm_logo.ch8", m)) return -1;

    // uint8_t testROM[] = {
    //     0x60, 0x1C, 
    //     0x61, 0x0C, 
    //     0xA2, 0x0A, 
    //     0xD0, 0x18, 
    //     0x12, 0x08, 
        

    //     0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C 
    // };

    // for (int j = 0; j < sizeof(testROM); j++) {
    //     m[0x200 + j] = testROM[j];
    // }

    // if (!ROM("ibm_logo.ch8", m)) return -1;

    // CUSTOM KOSS GAME: "Dot Hunter" (WASD to catch the random teleporting dot)
    uint8_t customGame[] = {
        0x60, 0x20, 
        0x61, 0x10, 
        0xC2, 0x3F, 
        0xC3, 0x1F, 
        0xA2, 0x34, 
        
        0x00, 0xE0, 
        0xD2, 0x31, 
        0xD0, 0x11, 
        
        0x3F, 0x01, 
        0x12, 0x18, 
        0xC2, 0x3F, 
        0xC3, 0x1F, 
        
        0xF4, 0x0A, 
        
        0x34, 0x04,
        0x12, 0x20, 
        0x70, 0xFF, 
        
        0x34, 0x06, 
        0x12, 0x26,
        0x70, 0x01,
        
        0x34, 0x02,
        0x12, 0x2C,
        0x71, 0xFF,
        
        0x34, 0x08,
        0x12, 0x32,
        0x71, 0x01,
        
        0x12, 0x0A,
        
        0x80
    };

    for (int j = 0; j < sizeof(customGame); j++) {
        m[0x200 + j] = customGame[j];
    }

    // cout << "Manual Test ROM loaded!" << endl;
    while (true)
    {
        uint16_t opcode = (m[pc]<<8) | m[pc+1];
        // cout << "PC: " << hex << pc << " Opcode: " << opcode << dec << " ";
        pc+=2;
        
        uint8_t  x   = (opcode & 0x0F00) >> 8;
        uint8_t  y   = (opcode & 0x00F0) >> 4;
        uint8_t  n   = (opcode & 0x000F);
        uint8_t  kk  = (opcode & 0x00FF);
        uint16_t nnn = (opcode & 0x0FFF);  
        switch (opcode & 0xF000) {
                case 0x0000:
                if (opcode == 0x00E0) {
                    for (int p = 0; p < 2048; p++) {
                        display[p] = 0;
                    }
                }
                else if (opcode == 0x00EE) {
                    sp--;
                    pc = s[sp];
                }
                break;

            case 0x1000:
                pc = nnn;
                break;
            case 0x2000:
                s[sp] =pc;
                sp++;
                pc =nnn;
                break;
            case 0x3000:
                if (v[x] == kk) {
                    pc += 2;
                }
                break;
            case 0x6000:
                
                v[x] = kk;
                break;

            case 0x7000:
            
                v[x] += kk;
                break;

            case 0xA000:
                
                i = nnn;
                break;
            case 0xD000:{
                uint8_t xAxis = v[x]%64;
                uint8_t yAxis = v[y]%32;
                v[0xF]=0;
                for (int row = 0; row < n; row++)
                {
                    uint8_t spriteByte = m[i+row];
                    for (int col = 0; col < 8; col++) {
                        uint8_t spritePixel = spriteByte & (0x80 >> col);
                        int screenPixelIndex = ((yAxis + row) % 32) * 64 + ((xAxis + col) % 64);
                        if (spritePixel != 0) {
                            if (display[screenPixelIndex] == 1) {
                                v[0xF] = 1;
                            }
                            display[screenPixelIndex] ^= 1;
                        }
                    }
                }
                break;
            }
            case 0xC000:
                v[x] = (rand() % 256) & kk;
                break;
            case 0xF000:
                if (kk == 0x0A) {
                    system("cls");
                    for (int r = 0; r < 32; r++) {
                        for (int c = 0; c < 64; c++) {
                            if (display[r * 64 + c] == 1) cout << "\xDB\xDB";
                            else cout << "  ";
                        }
                        cout << endl;
                    }

                    char key = _getch();
                    
                    if (key == 'a' || key == 'A' || key == '4') v[x] = 0x04;
                    else if (key == 'd' || key == 'D' || key == '6') v[x] = 0x06;
                    else if (key == 'w' || key == 'W' || key == '2') v[x] = 0x02;
                    else if (key == 's' || key == 'S' || key == '8') v[x] = 0x08;
                    else v[x] = 0x00;
                }
                break;

            }
    }



 return 0;
}