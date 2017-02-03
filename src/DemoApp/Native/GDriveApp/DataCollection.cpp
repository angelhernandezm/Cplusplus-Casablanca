#include "pch.h"
#include "DataCollection.h"

using namespace RestOperations;

DataCollection::DataCollection() {
	m_items = ref new Platform::Collections::Vector<RestOperations::Photo^>();
}

void DataCollection::SetItems(Windows::Foundation::Collections::IVector<RestOperations::Photo^>^ photos) {
	int count;
	m_items->Clear();

	if (photos != nullptr && (count = photos->Size) > 0) {
		for (auto index = 0; index < count; index++) {
			m_items->Append(photos->GetAt(index));
		}
	}
}

Windows::UI::Xaml::Interop::IBindableObservableVector^ DataCollection::Items::get() {
	return m_items;
}