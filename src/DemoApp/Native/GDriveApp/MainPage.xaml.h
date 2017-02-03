//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
//#include "Photo.h"
#include "DataCollection.h"
#include <collection.h>
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/uri.h"
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/http_msg.h"
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/http_client.h" 
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/containerstream.h" 
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/filestream.h" 
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/interopstream.h" 
#include "packages/cpprestsdk.1.4.0/build/native/include/cpprest/rawptrstream.h" 


using namespace GDriveApp;
using namespace RestOperations;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace Windows::UI::Popups;

namespace GDriveApp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		Windows::UI::Xaml::Media::Imaging::BitmapImage^ m_Image;


		pplx::task<void> GetPhotos();
		RestOperations::DataCollection^ m_data;
		void GetPicture(int photoId);
		Windows::Storage::StorageFile^ m_fileToUpload;
		Windows::UI::Core::CoreDispatcher^ m_dispatcher;
		Windows::Storage::Streams::DataWriter^ m_dataWriter;
		Windows::Storage::Streams::InMemoryRandomAccessStream^ m_imageStream;
		Platform::Collections::Vector<RestOperations::Photo^>^ m_filesAvailable;
		pplx::task<void> UploadPicture(Platform::String^ pictureToUpload, Platform::String^ notes);
		void btnGetPhotos_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnUploadPhoto_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ItemListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
	};
}
