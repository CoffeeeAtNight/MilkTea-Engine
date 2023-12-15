#include <vector>
#include <string>

class IUuidFactory {
public:
	virtual std::string generateUuid() = 0;
	virtual ~IUuidFactory();
};