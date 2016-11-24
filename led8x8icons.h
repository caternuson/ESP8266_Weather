//===============================================================================
// led8x8icons.py
//
// Dictionary of LED 8x8 matrix icons as 64 bit values.
//
// Code snippet for setting individual LEDs on the display.
//
//        void set_raw64(uint64_t value) {
//          uint8_t row_byte, pixel_bit;
//          for (int y=0; y<=7; y++) {
//            row_byte = value >> (8*y);
//            for (int x=0; x<=7; x++) {
//              pixel_bit = row_byte >> x & 0x01;
//              matrix.drawPixel(x, y, pixel_bit);
//            }
//          }
//          matrix.writeDisplay();
//        }
//
// 2016-11-24
// Carter Nelson
//==============================================================================
//--------------------------------------------------------
// misc
//--------------------------------------------------------
#define ICON_ALL_ON                     0xffffffffffffffff
#define ICON_ALL_OFF                    0x0000000000000000
#define ICON_UNKNOWN                    0x00004438006c6c00
#define ICON_BOTTOM_ROW                 0xff00000000000000
#define ICON_TOP_ROW                    0x00000000000000ff
#define ICON_LEFT_COL                   0x0101010101010101
#define ICON_RIGHT_COL                  0x8080808080808080
#define ICON_BOX                        0xff818181818181ff
#define ICON_XBOX                       0xffc3a59999a5c3ff
//--------------------------------------------------------
// weather
//--------------------------------------------------------
#define ICON_SUNNY                      0x9142183dbc184289
#define ICON_RAIN                       0x55aa55aa55aa55aa
#define ICON_CLOUD                      0x00007e818999710e
#define ICON_SHOWERS                    0x152a7e818191710e
#define ICON_SNOW                       0xa542a51818a542a5
#define ICON_STORM                      0x0a04087e8191710e
//--------------------------------------------------------
// digits
//--------------------------------------------------------
#define ICON_0                          0x003c42464a52623c
#define ICON_1                          0x003e0808080e0808
#define ICON_2                          0x007e02023c40403e
#define ICON_3                          0x003e40403040403e
#define ICON_4                          0x004040407e424242
#define ICON_5                          0x003e40403e02027e
#define ICON_6                          0x003c42423e02027c
#define ICON_7                          0x004040404042427e
#define ICON_8                          0x003c42423c42423c 
#define ICON_9                          0x003c40407c42423c
//--------------------------------------------------------
// kanji digits
//--------------------------------------------------------
#define ICON_KANJI_0                    0x3c4281818181423c
#define ICON_KANJI_1                    0x000000ff00000000
#define ICON_KANJI_2                    0x00ff0000007e0000
#define ICON_KANJI_3                    0xff00003c00007e00
#define ICON_KANJI_4                    0x81ff81b3d59595ff
#define ICON_KANJI_5                    0xff44487e08087e00
#define ICON_KANJI_6                    0x81422400ff080804
#define ICON_KANJI_7                    0x788808087e080800
#define ICON_KANJI_8                    0xc162241414141400
#define ICON_KANJI_9                    0x61a22424243f0404
