using namespace Platform;
using namespace Windows::Foundation;

namespace GDriveApp {
	class StringUtil {
	public:
		static Platform::String^ ParseException(const char* ex);
	};
}