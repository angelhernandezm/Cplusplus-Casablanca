#include "Photo.h"


namespace RestOperations {
	using namespace Platform;
	using namespace Windows::Foundation;

	public ref class DataCollection sealed {
	private:
		Windows::UI::Xaml::Interop::IBindableObservableVector^  m_items;

	public:
		DataCollection();
		void SetItems(Windows::Foundation::Collections::IVector<RestOperations::Photo^>^ photos);
		property  Windows::UI::Xaml::Interop::IBindableObservableVector^ Items {
			Windows::UI::Xaml::Interop::IBindableObservableVector^ get();
		}
	};
}