#include "pch.h"
#include "Photo.h"

using namespace RestOperations;

Photo::Photo() {

}

Photo::Photo(int photoId, String^ name, String^ notes, DateTime createdOn) {
	PhotoId = photoId;
	Name = name;
	Notes = notes;
	CreatedOn = createdOn;
}

void Photo::OnPropertyChanged(Platform::String^ propertyName) {
	auto args = ref new  Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName);
	_PropertyChanged(this, args);
}

int Photo::PhotoId::get() {
	return m_photoId;
}

void Photo::PhotoId::set(int value) {
	m_photoId = value;
	OnPropertyChanged("PhotoId");
}

String^ Photo::Name::get() {
	return m_name;
}

void Photo::Name::set(String^ value) {
	m_name = value;
	OnPropertyChanged("Name");
}

String^ Photo::Notes::get() {
	return m_notes;
}

void Photo::Notes::set(String^ value) {
	m_notes = value;
	OnPropertyChanged("Notes");
}

DateTime Photo::CreatedOn::get() {
	return m_createdOn;
}

void Photo::CreatedOn::set(DateTime value) {
	m_createdOn = value;
	OnPropertyChanged("CreatedOn");
}
