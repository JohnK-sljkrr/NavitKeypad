
//****************** Copyright (c) 2020 Firestone Robot Foundry.***************
//
//  File:         /home/johnk/Development/RpiNavit/NavitKeypad/NaviKeypad.ino
//
//  Summary:      USB Keypad for Navit on RPI
//
//  Contents:
//
//  Notes:
//
//  Author:       John Kabat
//
//  Last Edit:    6/6/2020 19:39:01 By: John Kabat
//
//  Revisions:
//
//*****************************************************************************

//**********************************************************************************
// Direct Keys and their functions
//
// = -Zoom in( Unshifted "+" key )
// - - (minus key)Zoom Out
// 3 - Toggle 3D
// a - Auto Zoom
// b - Go to Bookmark Menu
// c - Center Cursor
// (cap)D - toggle day/night mode
// f - Toggle Fullscreen
// (Cap)F - Follow - Not Implemented
// (Cap)H - Set Destination Home  - Not Implemented yet
// m - Main Menu
// n - Toggle north or direction
// (cap)N - Set map Navigation
// r - Zoom to Route
// (Cap)P -Power off
// s - Toggle Announcer(speech)
// T - Toggle Tracking
// W - World - not implemented
// X - not implemented
// Y - not implemented
// Z - not implemented
// * - Star - Not used
//
// q - Quit Navit
// Esc - escape also acts as enable key for Shift-F4
//  Shift F4 - Sends Shift-F4 if enabled otherwise nothing
//**********************************************************************************
//**********************************************************************************
//*
//* Keyboard Layout
//
//
// keyboard goes left to right
//*      (col/row)
//* |---------------------------|
//- |  5-Way Arrow Switch       | C
//* |                           |
//* |           UP (5/1)        |
//* |                           |
//* | LEFT    ENTER   RIGHT     |
//* | (5/2)    (5/2)   (5/3)    |
//* |         DOWN              |
//* |          (5/6)            |
//* |---------------------------|
//* |             |             |
//* |    = (+)    |      -      |
//* |  Zoom In    |   Zoom out  |
//* |    (1/1))   |    (2/1)    |
//* |-------------|-------------|
//* |             |             |
//* |    c        |      3      |
//* | Re-Center   | 3D/2D Toggle|
//* |  (1/2)      |    (2/2)    |
//* |-------------|-------------|
//* |             |             |
//* |      b      |      a      |
//* | Bookmarks   |  AutoZoom   |
//* |    (1/3)    |   Toggle    |
//* |             |    (2/3)
//* |---------------------------|
//* |             |             |
//* |    r        |      n      |
//* |Show Route   | North/Travel|
//* |             |Direcion/Tog |
//* |   (1/4)     |   (2/4)     |
//* |-------------|-------------|
//* |             |             |
//* |     F       |     T       |
//* |  Follow Mode|  Tracking   |
//* |    (1/5)    |    (2/5)    |
//* |-------------|-------------|
//* |             |             |
//* |    m        |     f       |
//* | Main Menu   |   Toggle    |
//* |             | Fullscreen  |
//* |   (3/1)     |   (4/1)     |
//* |-------------|-------------|
//* |             |             |
//* |      H      |     D       |
//* |  Set Dest   |  Day/Night  |
//* |  Home Macro |             |
//* |    (3/2)    |   (4/2)     |
//* | ------------|-------------|
//* |             |             |
//* |     s       |     x       |
//* |    Toggle   |             |
//* |    Sound    |             |
//* |   (3/3)     |   (4/3)     |
//* | ------------|-------------|
//* |             |             |
//* |   Shift     |     p       |
//* | Special     | shift Power |
//* |    (3/4)    |    (4/4)    |
//* | ------------|-------------|
//* |             |             |
//* |   Shift F4  |      W      |
//* |  To Work    |             |
//* |    (3/5)    |   (4/5)     |
// *|-------------|-------------|


//**********************************************************************************
#include <Keypad.h>

#include<BounceJK.h>
//*********************************************************************************
//   Pin Definitions for Teensy 3.2
//*********************************************************************************

// Buttons
const uint8_t  bRow1            = 3;                                    // brown
const uint8_t  bRow2            = 4;                                    // red
const uint8_t  bRow3            = 5;                                    // orange
const uint8_t  bRow4            = 6;                                    // yellow
const uint8_t  bRow5            = 7;                                    // green

const uint8_t  bCol1            = 8;                                    // blue
const uint8_t  bCol2            = 9;                                    // violet
const uint8_t  bCol3            = 10;                                   // gray
const uint8_t  bCol4            = 11;                                   //  white
const uint8_t  bCol5            = 12;                                   // black

const uint8_t  ROWS             = 5;
const uint8_t  COLS             = 5;


uint8_t        rowPins[ROWS]    = {
    bRow1, bRow2, bRow3, bRow4, bRow5
                    };
uint8_t        colPins[COLS]    = {
    bCol1, bCol2, bCol3, bCol4, bCol5
                    };


//*********************************************************************************
//  Button output Codes
//*********************************************************************************

// codes for buttons in matrix
// column 1
const uint16_t bt1              = 1;                                     // = Zoom in
const uint16_t bt2              = 2;                                     // c - re-center
const uint16_t bt3              = 3;                                     // b - bookmarks
const uint16_t bt4              = 4;                                     // r - Show Route
const uint16_t bt5              = 5;                                     // F - Follow mode
// column 2
const uint16_t bt6              = 6;                                     //  - zoom out
const uint16_t bt7              = 7;                                     //  3 - 2d/2d toggle
const uint16_t bt8              = 8;                                     //  a - Autozoom toggle
const uint16_t bt9              = 9;                                     //  n - north/travel direction toggle
const uint16_t bt10             = 10;                                   //   T - Tracking
// column 3
const uint16_t bt11             = 11;                                   //  m - Menu
const uint16_t bt12             = 12;                                   //  H - set Home as dest
const uint16_t bt13             = 13;                                   //  s - Sound toggle
const uint16_t bt14             = 14;                                   // shift
const uint16_t bt15             = 15;                                   //  F4
// column 4
const uint16_t bt16             = 16;                                   // N - Set Navigation
const uint16_t bt17             = 17;                                   // D - Toggle Day Night Mode
const uint16_t bt18             = 18;                                   // X - w/shift cancel navigation
const uint16_t bt19             = 19;                                   // p - W/shift Power Off
const uint16_t bt20             = 20;                                   // W - Open
// column 5                                           //
// 5 way arrow key switch                             //
const uint16_t AR1              = 21;                                    //
const uint16_t AR2              = 22;                                    //
const uint16_t AR3              = 23;                                    //
const uint16_t AR4              = 24;                                    //
const uint16_t AR5              = 25;                                    //

// define the keypad button matrix
// this is a 5x5 matrix so  we can have up to 25 keys
// Note:  rows and cols are reversed
uint8_t        matrixKeys[ROWS][COLS] = {
    { bt1, bt6, bt11, bt16, AR1 },                          // row bRow1
    { bt2, bt7, bt12, bt17, AR2 },                          // row bRow2
    { bt3, bt8, bt13, bt18, AR3 },                          // row bRow3
    { bt4, bt9, bt14, bt19, AR4 },                          // row bRow4
    { bt5, bt10, bt15, bt20, AR5 },                         // row bRow15
};

void dummy( void );
// Special code flags
typedef enum {
    NO_FLAGS = 0,
    IS_MODIFIER = 1,
    SHIFT_REQUIRED = 2,
    IS_MACRO = 0x80,
    MACRO_DELAY = IS_MACRO + 1,
    MACRO_DONE = 0xAF
}myKeyFlags;

struct KEY_MACRO
{
    myKeyFlags flags;
    uint16_t   key;
    uint16_t   modifier;
    KeyState   keystate;
};
struct ButtonCode
{
    myKeyFlags       flags;
    uint16_t         key;
    uint16_t         modifier;
    KEY_MACRO        *p;
    KeyState         keystate;
};

struct KEY_MACRO SetDestHome[]    =
   {
    { NO_FLAGS, KEY_M },                                    // main menu 1st
    // Select Actions
    // stop Navigation
    // backup to main menu
    // Bookmarks
    // select Our Home
    // Set As Destination


       { MACRO_DONE, 0 },                                      // zoom in (Actually for plus key so we don't have to shift
   };

ButtonCode       ButtonCodes[]    = {
    { NO_FLAGS, KEY_EQUAL },                                // zoom in (Actually for plus key so we don't have to shift
                   { NO_FLAGS, KEY_C },                                    // Re-center
                   { NO_FLAGS, KEY_B },                                    // Bookmarks
                   { NO_FLAGS, KEY_R },                                    // Show Route
                   { NO_FLAGS, KEY_F, MODIFIERKEY_SHIFT },                 // Toggle follow Mode    (Needs to be uppercase?)

                   { NO_FLAGS, KEY_MINUS },                                // Zoom Out
                   { NO_FLAGS, KEY_3 },                                    // Toggle 3D
                   { NO_FLAGS, KEY_A },                                    // Toggle Autozoom
                   { NO_FLAGS, KEY_N },                                    // Toggle North or Direction
                   { NO_FLAGS, KEY_T, MODIFIERKEY_SHIFT },

                   { NO_FLAGS, KEY_M },                                    // Menu
                   { NO_FLAGS, KEY_H, MODIFIERKEY_SHIFT },                 //  Cancel nav and show bookmarks
                   { NO_FLAGS, KEY_S },                                    // Toggle Speaker
                   { NO_FLAGS, MODIFIERKEY_SHIFT },                        // Shift  Enable key for Shift-F4
                   { NO_FLAGS, KEY_F4 },                                   // Shift-F4 Needs esc to enable

                   { NO_FLAGS, KEY_F },                                    // toggle fullscreen
                   { NO_FLAGS, KEY_D, MODIFIERKEY_SHIFT },                 // Toggle Day/Night
                   { NO_FLAGS, KEY_X },                                    // X
                   { NO_FLAGS, KEY_P },                                    // p )if shif power key
                   { NO_FLAGS, KEY_P },                                    // w

    // 5way arrow key switch
                   { NO_FLAGS, KEY_UP },                                   // Up Arrow
                   { NO_FLAGS, KEY_DOWN },                                 // Down Arrow
                   { NO_FLAGS, KEY_LEFT },                                 // Left Arrow
                   { NO_FLAGS, KEY_RIGHT },                                // Right Arrow
                   { NO_FLAGS, KEY_ENTER },                                // Enter key
               };


Keypad           myKeypad         = Keypad( makeKeymap( matrixKeys ) , rowPins, colPins, ROWS, COLS );

// mouse stuff

int16_t          mouseXcenter     = 508;
int16_t          mouseYcenter     = 553;
int              mouseDeadZone    = 50;
int16_t          mouseXposition   = 0;
int16_t          mouseYposition   = 0;

uint8_t          mouseMode        = 0xff;
uint8_t          mouseButtons     = 0xff;

Bounce           LeftMouseButton  = Bounce( );
Bounce           RightMouseButton = Bounce( );

int16_t          mouse_x;
int16_t          mouse_y;

#if 0
bool getMouseMode( void )
{
    uint8_t mm = 0;;

    mm = ((digitalRead( mmaPin ) == LOW ? 1 : 0) | (digitalRead( mmbPin ) == LOW ? 2 : 0) );
    // see if in transition
    if ( mm == 0 )
    {
        return ( false );
    }
    if ( mm != mouseMode )
    {
        mouseMode = mm;
        Serial.print( "New MouseMode: 0x" );
        Serial.println( mouseMode, HEX );
        return ( true );
    }
    return ( false );
}

void setupMouse( void )
{

    pinMode( mmaPin, INPUT_PULLUP );
    pinMode( mmbPin, INPUT_PULLUP );
    pinMode( lmPin, INPUT_PULLUP );
    pinMode( rmPin, INPUT_PULLUP );
    pinMode( mUDPin, INPUT );
    pinMode( mLRPin, INPUT );
    //setup debounce
    LeftMouseButton.attach( lmPin );
    LeftMouseButton.interval( 30 );
    RightMouseButton.attach( rmPin );
    RightMouseButton.interval( 30 );
    Mouse.screenSize( 1920, 1080 );

    // assume when we state no one is touching the mouse
    // set the center
    mouseXcenter = analogRead( mLRPin ) & ~(3);
    mouseYcenter = analogRead( mUDPin ) & ~(3);
    Serial.print( "Mouse Center  x:" );
    Serial.println( mouseXcenter );
    Serial.print( " y:" );
    Serial.print( mouseYcenter );
    Serial.println( );

}

bool getMouseButtons( void )
{
    uint8_t mb = 0;

    mb = ((digitalRead( lmPin ) == LOW ? 1 : 0) | (digitalRead( rmPin ) == LOW ? 2 : 0) );

    if ( mb != mouseButtons )
    {
        mouseButtons = mb;

        Serial.print( "New Buttons: 0x" );
        Serial.println( mouseButtons, HEX );
        return ( true );
    }
    return ( false );
}

bool readMousePosition( void )
{
    bool ret = false;
    uint16_t x;
    uint16_t y;
    int dzxl,
    dzxh,
    dzyl,
    dzyh;

    dzxl = mouseXcenter - mouseDeadZone;
    dzxh = mouseXcenter + mouseDeadZone;
    dzyl = mouseYcenter - mouseDeadZone;
    dzyh = mouseYcenter + mouseDeadZone;
    x = analogRead( mLRPin );
    y = analogRead( mUDPin );
    // clear out 2 or 3 ls bits to reduce chatter
    y &= ~(3);
    x &= ~(3);

    // if both in dead zone then nothing to do
    if ( (x >= dzxl && x <= dzxh) &&
        (y >= dzyl && y <= dzyh) )
    {
        return ( ret );
    }
    // we need to check if mouse position changed
    // and only report if so
    if ( (mouseXposition != x) ||
        (mouseYposition != y) )
    {
        mouseXposition = x;
        mouseYposition = y;
        ret = true;
    }
    if ( ret )
    {

        Serial.print( "Mouse x:" );
        Serial.print( x );
        Serial.print( " y:" );
        Serial.print( y );
        Serial.println( " OK" );
        mouseXposition = x;
        mouseYposition = y;
        delay( 200 );
    }
    return ( ret );
}
#else
bool getMouseMode( void )
{
    return ( false );
}
void setupMouse( void )
{
}
bool getMouseButtons( void )
{
    return ( false );
}
bool readMousePosition( void )
{
    return ( false );
}
#endif

void KeyPressed( uint16_t key, KeyState state )
{

    uint16_t   k;
    uint16_t   m;
    myKeyFlags f;

    k = ButtonCodes[key].key;
    m = ButtonCodes[key].modifier;
    f = ButtonCodes[key].flags;
    ButtonCodes[key].keystate = state;
    Serial.print( key );
    Serial.print( " 0x" );
    Serial.print( k, HEX );
    Serial.print( " 0x" );
    Serial.print( m, HEX );
    Serial.print( " F:" );
    Serial.print( f );
    Serial.println( );
    // // alt f4 key??
    // if ( f == SPECIAL_KEY_1 )
    // {
    //     // see if key above is also  pressed
    //     Serial.print( "Above key:" );
    //     Serial.println( ButtonCodes[key - 1].keystate );
    //     if ( ButtonCodes[key - 1].keystate != HOLD )        // key above
    //     {
    //         // just set to idle
    //         return;                                         // not yet just ignore
    //     }
    // }
    if ( state == PRESSED )
    {
        if ( m )                                            // have modifier
        {
            Keyboard.press( m );
        }
        if ( k )                                            // have key
        {
            Keyboard.press( k );
        }
    }
    if ( state == RELEASED )
    {
        if ( k )                                            // have key
        {
            Keyboard.release( k );
        }
        if ( m )                                            // have modifier
        {
            Keyboard.release( m );
        }
    }
}

bool myGetKeys( void )
{
    bool   ret = false;
    int    i   = 0;
    String msg;

    if ( myKeypad.getKeys( ) )
    {
        for ( i = 0; i < LIST_MAX; i++ )                    // Scan the whole key list.
        {
            if ( myKeypad.key[i].stateChanged )             // Only find keys that have changed state.
            {
                switch ( myKeypad.key[i].kstate )           // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                {
                    case PRESSED:
                    {
                        msg = " PRESSED.";
                        ret = true;
                        break;
                    }
                    case HOLD:
                    {
                        msg = " HOLD.";
                        break;
                    }
                    case RELEASED:
                    {
                        msg = " RELEASED.";
                        ret = true;
                        break;
                    }
                    case IDLE:
                    {
                        msg = " IDLE.";
                        break;
                    }
                }

                KeyPressed( myKeypad.key[i].kchar - 1, myKeypad.key[i].kstate );
                if ( ret )
                {
                    Serial.print( "Key " );
                    Serial.print( (int)(myKeypad.key[i].kchar) );
                    Serial.print( " " );
                    Serial.print( myKeypad.key[i].kcode );
                    Serial.print( msg );
                    KeyPressed( myKeypad.key[i].kchar - 1, myKeypad.key[i].kstate );
                }
            }

        }
    }
    return ( ret );

}

void setup( void )
{
    Serial.begin( 115200l );
    // mouse pins
    setupMouse( );
    getMouseMode( );
    getMouseButtons( );
}

void loop( void )
{

    uint16_t k;
    uint16_t m;
    uint8_t  customKey;

    myGetKeys( );

    customKey = myKeypad.getKey( );
    if ( customKey )
    {
        k = ButtonCodes[customKey - 1].key;
        m = ButtonCodes[customKey - 1].modifier;
        Serial.print( customKey );
        Serial.print( " 0x" );
        Serial.print( k, HEX );
        Serial.print( " 0x" );
        Serial.print( m, HEX );
        Serial.println( );
        if ( m )                                            // have modifier
        {
            Keyboard.press( m );
        }
        if ( k )                                            // have key
        {
            Keyboard.press( k );
            delay( 10 );
            Keyboard.release( k );
        }
        if ( m )                                            // have modifier
        {
            Keyboard.release( m );
        }

    }
    // mouse stuff
    getMouseMode( );                                        // see if changed
    if ( LeftMouseButton.update( ) )                        // left button changed
    {
        Serial.print( "Left Mouse Button " );
        if ( LeftMouseButton.fell( ) )
        {
            Serial.print( "Pressed" );
        }
        else
        {
            Serial.print( "Released" );
        }
        Serial.println( );
    }
    if ( RightMouseButton.update( ) )                       // Right button changed
    {
        Serial.print( "Right Mouse Button " );
        if ( RightMouseButton.fell( ) )
        {
            Serial.print( "Pressed" );
        }
        else
        {
            Serial.print( "Released" );
        }
        Serial.println( );
    }
    readMousePosition( );
}
