#include "pch.h"
#include "ImageSource.h"

using namespace RestOperations;

ImageSource::ImageSource(Windows::UI::Core::CoreDispatcher^ dispatcher) {
	m_dispatcher = dispatcher;
}

Windows::UI::Xaml::Media::Imaging::BitmapImage^ ImageSource::Bitmap::get() {
	return m_bitmap;
}

Windows::Storage::Streams::DataWriter^ ImageSource::DataWriter::get() {
	return m_dataWriter;
}

Windows::Storage::Streams::InMemoryRandomAccessStream^ ImageSource::RandomStream::get() {
	return m_randomStream;
}

void ImageSource::CreateBitmap() {
	m_bitmap = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	m_bitmap->SetSource(m_randomStream);
}


void ImageSource::Reset(Windows::Storage::Streams::DataWriter^ dataWriter, Windows::Storage::Streams::InMemoryRandomAccessStream^ randomStream) {
	m_dataWriter = dataWriter;
	m_randomStream = randomStream;
}