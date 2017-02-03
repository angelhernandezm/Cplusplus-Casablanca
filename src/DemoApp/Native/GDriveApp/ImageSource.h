namespace RestOperations {
	ref class ImageSource sealed {
	private:
		Windows::UI::Core::CoreDispatcher^ m_dispatcher;
		Windows::Storage::Streams::DataWriter^ m_dataWriter;
		Windows::UI::Xaml::Media::Imaging::BitmapImage^ m_bitmap;
		Windows::Storage::Streams::InMemoryRandomAccessStream^ m_randomStream;
	public:
		ImageSource(Windows::UI::Core::CoreDispatcher^ dispatcher);
		
		property Windows::UI::Xaml::Media::Imaging::BitmapImage^ Bitmap	{
			Windows::UI::Xaml::Media::Imaging::BitmapImage^ get();
		}

		property Windows::Storage::Streams::DataWriter^ DataWriter	{
			Windows::Storage::Streams::DataWriter^ get();
		}

		property Windows::Storage::Streams::InMemoryRandomAccessStream^ RandomStream {
			Windows::Storage::Streams::InMemoryRandomAccessStream^ get();
		}

		void CreateBitmap();

		void Reset(Windows::Storage::Streams::DataWriter^ dataWriter, Windows::Storage::Streams::InMemoryRandomAccessStream^ randomStream);
	};
}