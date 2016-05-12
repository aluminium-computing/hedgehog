// Read from keyboard: interactivity at last!


#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL

#include "hedge"

#define   SHIFT_KEY 0x01 // 001
#define CONTROL_KEY 0x02 // 010
#define     ALT_KEY 0x04 // 100
//#define AL_KEY (SHIFT_KEY | CONTROL_KEY | ALT_KEY) // 111
char kbd;
char modifierKeys = 0;


// KeyBoarD for ENglish used in Aim City
unsigned char kbdenac[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',
  '\t',
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    CONTROL_KEY,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '\n',   SHIFT_KEY,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/',   SHIFT_KEY,
  '*',
    ALT_KEY,
  ' ',
    0,
    0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,
    0,
    0,
    0,
    0,
    0,
  '-',
    0,
    0,
    0,
  '+',
    0,
    0,
    0,
    0,
    0,
    0,   0,   0,
    0,
    0,
    0,
};

unsigned char shiftedKeys[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',
  '\t',
  'Q', 'W', 'E', 'R',
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
 '\"', '~',  0,
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',
  'M', '<', '>', '?',   0,
  '*',
    0,
  ' ',
    0,
    0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,
    0,
    0,
    0,
    0,
    0,
  '-',
    0,
    0,
    0,
  '+',
    0,
    0,
    0,
    0,
    0,
    0,   0,   0,
    0,
    0,
    0,
};

void HHKeyboardHandler(struct regs *r)
{
    unsigned char scancode, code;

    scancode = HHGetCharFromPort(0x60);

    if (scancode & 0x80)
    {
      // These are break codes
      code = kbdenac[scancode ^ 0x80];
      if (code < 8 && code > 0) {
        // If code is a modifier, we want to turn OFF the bits of code in
        // modifier keys. So we AND modifierKeys with the complement of |code|.
        // The complement of 010 is 101.
        modifierKeys &= ~code;
        code = 0;
      }
    }
    else
    {
        code = kbdenac[scancode];
        if (code < 8 && code > 0) {
          modifierKeys |= code;
          code = 0;
        }
        if (modifierKeys & SHIFT_KEY) {
          code = shiftedKeys[scancode];
        }
				HHPrintChar(code);
				// DEBUG: print whether modifier key bits are set with each keypress
				// HHPrintChar(48 + modifierKeys);
        kbd = code;
    }
    #ifdef DEBUG
    if (code == ';' && (modifierKeys & CONTROL_KEY)) {
      HHCrash("0x15_21_INTENT");
    }
    #endif // DEBUG
}

char HHGetCharFromKbd() {
  char retval = kbd;
  kbd = NULL;
  return retval;
}





char *HHGetStringFromKBD(len len_) {
  char *string = (char *)HHAlloc(len_);
  int i = 0;
  while (i < len_) {
    string[i] = HHGetCharFromKbd();
		i++;
  }
  return string;
}

void HHInstallKeyboard() {
  irq_install_handler(1, HHKeyboardHandler);
}
