#ifndef WLIB_SCHEDULER_H
#define WLIB_SCHEDULER_H

#include <Scheduler.h>

namespace wlp {
    class Tasker {
#if defined(TEENSYDUINO)
        /** Default stack size and stack max. */
  static const size_t DEFAULT_STACK_SIZE = 1024;
  static const size_t DEFAULT_MAIN_STACK_SIZE = 2048;
#if defined(__MK20DX256__)
  /** Teensy 3.2: 64 Kbyte. */
  static const size_t STACK_MAX = 16384;
#elif defined(__MK64FX512__)
  /** Teensy 3.5: 192 Kbyte. */
  static const size_t STACK_MAX = 49152;
#elif defined(__MK66FX1M0__)
  /** Teensy 3.6: 256 Kbyte. */
  static const size_t STACK_MAX = 65536;
#else
#error "Scheduler.h: Teensy board not supported"
#endif

#elif defined(ARDUINO_ARCH_AVR)
        /** Default stack size. Stack max dynamically checked against heap end. */
        static const size_t DEFAULT_STACK_SIZE = 128;
        static const size_t DEFAULT_MAIN_STACK_SIZE = 256;

#elif defined(ARDUINO_ARCH_SAM)
        /** Default stack size and stack max. */
  static const size_t DEFAULT_STACK_SIZE = 1024;
  static const size_t DEFAULT_MAIN_STACK_SIZE = 2048;
  static const size_t STACK_MAX = 32768;

#elif defined(ARDUINO_ARCH_SAMD)
  /** Default stack size and stack max. */
  static const size_t DEFAULT_STACK_SIZE = 1024;
  static const size_t DEFAULT_MAIN_STACK_SIZE = 2048;
  static const size_t STACK_MAX = 16384;

#else
#error "Scheduler.h: Arduino board not supported"
#endif
    public:
        typedef void (*func_t)();

        static inline bool begin(size_t stackSize) { return Scheduler.begin(stackSize); }

        static inline bool start(func_t taskSetup, func_t taskLoop,
                                 size_t stackSize = Tasker::DEFAULT_STACK_SIZE) {
            return Scheduler.start(taskLoop, taskLoop, stackSize);
        }

        static inline bool startLoop(func_t taskLoop, size_t stackSize = DEFAULT_STACK_SIZE) {
            return Scheduler.startLoop(taskLoop, stackSize);
        }

        static inline void yield() { Scheduler.yield(); }

        static inline size_t stack() { return Scheduler.stack(); }
    };
}

#endif //WLIB_SCHEDULER_H
