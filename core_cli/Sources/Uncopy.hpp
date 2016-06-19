#ifndef _Uncopy_h_
#define _Uncopy_h_

namespace Core {
class Uncopy {
public:
	explicit Uncopy() {
		//empty
	}
	virtual ~Uncopy() {
		//empty
	}

private:
	Uncopy(const Uncopy&) = delete;
	Uncopy(Uncopy&&) = delete;
	Uncopy& operator =(Uncopy) = delete;
	Uncopy& operator =(Uncopy&&) = delete;
};
// class Uncopy;

}
#endif // #ifndef _Uncopy_h_
