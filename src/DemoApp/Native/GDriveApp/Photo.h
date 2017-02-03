

namespace RestOperations {
	using namespace Platform;
	using namespace Windows::Foundation;

	[Windows::UI::Xaml::Data::Bindable]
	public ref class Photo sealed {
	private:
		int m_photoId;
		String^ m_name;
		String^ m_notes;
		DateTime m_createdOn;
		event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ _PropertyChanged;

	public:
		Photo();
		Photo(int photoId, String^ name, String^ notes, DateTime createdOn);
		
		void OnPropertyChanged(Platform::String^ propertyName);

		property int PhotoId {
			int get();
			void set(int value);
		}

		property String^ Name {
			String^ get();
			void set(String^ value);;
		}

		property String^ Notes {
			String^ get();
			void set(String^ value);
		}

		property DateTime CreatedOn {
			DateTime get();
			void set(DateTime value);
		}
	};
}

