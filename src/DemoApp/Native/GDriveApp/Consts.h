namespace RestOperations {
	using namespace Platform;

	public ref class Consts sealed {
	public:
		static property String^ GetPhotosServiceEndPointUrl {
			String^ get() {
				return "http://localhost:3927/photos/GetPhotos";
			}
		}

		static property String^ UploadPhotoServiceEndPointUrl {
			String^ get() {
				return "http://localhost:3927/photos/UploadPhoto";
			}
		}

		static property String^ GetPhotoServiceEndPointUrl {
			String^ get() {
				return "http://localhost:3927/photos/GetPhoto";
			}
		}
	};
}
