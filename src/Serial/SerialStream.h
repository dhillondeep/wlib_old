#ifndef WLIB_SERIAL_H
#define WLIB_SERIAL_H

namespace wlp{
	class SerialStream{
	public:
		void start(unsigned long baud);
	};

	extern wlp::SerialStream serialstream;
}


#endif //WLIB_SERIAL_H
