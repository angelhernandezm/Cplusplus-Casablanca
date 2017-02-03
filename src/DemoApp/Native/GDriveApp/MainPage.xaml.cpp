//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Consts.h"
#include "Utils.h"
#include <Robuffer.h>

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage() {
	InitializeComponent();
	m_data = ref new RestOperations::DataCollection();
	m_dispatcher = Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher;
	m_filesAvailable = ref new Platform::Collections::Vector<RestOperations::Photo^>();
}


void GDriveApp::MainPage::btnUploadPhoto_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
	picker->FileTypeFilter->Append(".jpg");
	picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary;

	pplx::task<Windows::Storage::StorageFile^>(picker->PickSingleFileAsync())
		.then([this](Windows::Storage::StorageFile^ selectedFile) {

		if (selectedFile != nullptr) {
			m_fileToUpload = selectedFile;
			UploadPicture(m_fileToUpload->Name, "My photo");
		}
	});
}


void GDriveApp::MainPage::btnGetPhotos_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	GetPhotos();
}


pplx::task<void> MainPage::GetPhotos() {
	http_client client(Consts::GetPhotosServiceEndPointUrl->Data());

	return client.request(methods::GET)
		.then([&](http_response response) -> pplx::task<json::value> {
		return (response.status_code() != status_codes::OK ?
			pplx::task_from_result(json::value()) : response.extract_json());
	}).then([&](pplx::task<json::value> previousTask) {
		m_filesAvailable->Clear();
		const json::value& value = previousTask.get();

		std::for_each(value.cbegin(), value.cend(), [&](std::pair<json::value, json::value> jsonResult) {
			auto newEntry = ref new RestOperations::Photo;
			m_dispatcher->RunAsync(
				Windows::UI::Core::CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([this, jsonResult, newEntry]() {
				std::for_each(jsonResult.second.cbegin(), jsonResult.second.cend(), [&](std::pair<json::value, json::value> selected) {
					auto key = selected.first.as_string();
					auto data = selected.second;
					if (data.is_object() && !data.is_null()) {
						// Not used
					} else if (data.is_string()) {
						if (wcscmp(L"Name", key.c_str()) == 0)
							newEntry->Name = ref new String(selected.second.as_string().c_str());
						else if (wcscmp(L"Notes", key.c_str()) == 0)
							newEntry->Notes = ref new String(selected.second.as_string().c_str());
						else if (wcscmp(L"CreatedOn", key.c_str()) == 0) {
							// Parse date here
						}
					} else if (data.is_number()) {
						newEntry->PhotoId = selected.second.as_integer();
					}
				});
				m_filesAvailable->Append(newEntry);

			}));
		});
	}).then([this]() {
		m_dispatcher->RunAsync(
			Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new Windows::UI::Core::DispatchedHandler([this]() {
			m_data->SetItems(m_filesAvailable);
			ItemListView->ItemsSource = m_data->Items;
		}));

	});
}


pplx::task<void> MainPage::UploadPicture(Platform::String^ pictureToUpload, Platform::String^ notes) {
	if (pictureToUpload != nullptr && !pictureToUpload->IsEmpty()) {
		auto serviceUrl = "/" + pictureToUpload + "/" + notes;

		return file_stream<unsigned char>::open_istream(this->m_fileToUpload)
			.then([this, pictureToUpload, notes](pplx::task<basic_istream<unsigned char>> previousTask) {
			try {
				http_client client(Consts::UploadPhotoServiceEndPointUrl->Data());
				auto fileStream = previousTask.get();
				fileStream.seek(0, std::ios::end);
				auto length = static_cast<size_t>(fileStream.tell());
				fileStream.seek(0, 0);
				http_request req;
				req.set_body(fileStream, length);
				req.set_method(methods::POST);
				req.headers().add(L"Content-Type", L"text/plain");
				req.headers().add(L"fileName", pictureToUpload->Data());
				req.headers().add(L"notes", notes->Data());
				return client.request(req).then([this, fileStream](pplx::task<http_response> previousTask) {
					fileStream.close();
					std::wostringstream ss;
					try {
						auto response = previousTask.get();
						auto body = response.body();
						if (response.status_code() == web::http::status_codes::OK)
							m_dispatcher->RunAsync(
							Windows::UI::Core::CoreDispatcherPriority::Normal,
							ref new Windows::UI::Core::DispatchedHandler([this]() {
							auto msgDlg = ref new Windows::UI::Popups::MessageDialog("File successfully uploaded.");
							msgDlg->ShowAsync();
						}));
					} catch (const http_exception& e) {
						m_dispatcher->RunAsync(
							Windows::UI::Core::CoreDispatcherPriority::Normal,
							ref new Windows::UI::Core::DispatchedHandler([this, e]() {
							auto msgDlg = ref new Windows::UI::Popups::MessageDialog(StringUtil::ParseException(e.what()));
							msgDlg->ShowAsync();
						}));
					}
				});
			} catch (const std::system_error& e) {
				m_dispatcher->RunAsync(
					Windows::UI::Core::CoreDispatcherPriority::Normal,
					ref new Windows::UI::Core::DispatchedHandler([this, e]() {
					auto msgDlg = ref new Windows::UI::Popups::MessageDialog(StringUtil::ParseException(e.what()));
					msgDlg->ShowAsync();
				}));

				return pplx::task_from_result();
			}
		});
	}
}

void GDriveApp::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	GetPhotos();
}


void GDriveApp::MainPage::GetPicture(int photoId) {
	wchar_t buf[20];
	_itow_s(photoId, buf, 10);
	auto id = ref new String(buf);
	http_request req(methods::GET);
	http_client client(Consts::GetPhotoServiceEndPointUrl->Data());
	req.headers().add(L"photoId", id->Data());

	client.request(req).then([this](pplx::task<http_response> previousTask) {
		auto response = previousTask.get();
		auto buffer = std::make_shared<container_buffer<std::vector<uint8_t>>>();
		response.body().read_to_end(*buffer).get();
		auto bytesVector = buffer->collection();
		m_dataWriter = nullptr;
		m_imageStream = nullptr;
		m_dataWriter = ref new Windows::Storage::Streams::DataWriter();
		m_imageStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();
		auto bytes = ref new Platform::Array<unsigned char>(bytesVector.size());

		for (auto x = 0; x < bytes->Length; x++)
			bytes[x] = bytesVector[x];

		m_dataWriter = ref new Windows::Storage::Streams::DataWriter(m_imageStream);
		m_dataWriter->WriteBytes(bytes);

		m_dispatcher->RunAsync(
			Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new Windows::UI::Core::DispatchedHandler([this, bytes]() {
			GUID newGuid;

			if (SUCCEEDED(CoCreateGuid(&newGuid))) {
				auto guid = Guid(newGuid);
				auto fileName = guid.ToString() + L".jpg";

				pplx::create_task(Windows::Storage::ApplicationData::Current->LocalFolder->CreateFileAsync(fileName,
					Windows::Storage::CreationCollisionOption::ReplaceExisting))
					.then([this, fileName, bytes](Windows::Storage::StorageFile^ file) {

					pplx::create_task(Windows::Storage::FileIO::WriteBytesAsync(file, bytes))
						.then([this, file, fileName](pplx::task<void> task) {
						OutputDebugString(file->Path->Data());
						m_Image = nullptr;
						auto uri = ref new Windows::Foundation::Uri("ms-appdata:///local/" + fileName);
						m_Image = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
						m_Image->UriSource = uri;
						imgPhoto->Source = m_Image;
					});
				});
			}
		}));
	});
}

void GDriveApp::MainPage::ItemListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e) {
	if (e->AddedItems->Size > 0) {
		auto selected = reinterpret_cast<RestOperations::Photo^>(e->AddedItems->GetAt(0));
		GetPicture(selected->PhotoId);
	}
}
