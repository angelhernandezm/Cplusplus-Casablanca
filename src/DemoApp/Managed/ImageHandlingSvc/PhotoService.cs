using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Activation;
using System.ServiceModel.Web;
using System.Text;
using ImageHandlingSvc.Common;
using ImageHandlingSvc.Data;

namespace ImageHandlingSvc {
	[AspNetCompatibilityRequirements(RequirementsMode = AspNetCompatibilityRequirementsMode.Allowed)]
	[ServiceBehavior(InstanceContextMode = InstanceContextMode.PerCall)]
	public class PhotoService : IImageHandlingSvc {
		private const int MaxBufferSize = 66560; // 65 kb

		/// <summary>
		/// Gets the photos.
		/// </summary>
		/// <returns>List{Photo}.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		[WebGet(UriTemplate = "GetPhotos")]
		public List<Photo> GetPhotos() {
			var retval = new List<Photo>();
			using (var data = new DataFactory()) {
				var photos = data.GetPhotos();

				if (photos.Any())
					photos.ForEach(x => retval.Add(new Photo() {
						PhotoId = x.PhotoId, CreatedOn = x.CreatedOn, Name = x.Name, Notes = x.Notes
					}));

			}

			return retval;
		}

		/// <summary>
		/// Uploads the photo.
		/// </summary>
		/// <param name="bytes">The bytes.</param>
		[WebInvoke(UriTemplate = "UploadPhoto", Method = "POST")]
		public void UploadPhotoCpp(Stream bytes)
		{
			var read = 0;
			var buffer = new byte[MaxBufferSize];
			var headers = WebOperationContext.Current.IncomingRequest.Headers;
			var fileName = headers["fileName"];
			var notes = headers["notes"];

			using (var ms = new MemoryStream()) {
				do {
					read = bytes.Read(buffer, 0, buffer.Length);
					ms.Write(buffer, 0, read);
				} while (read > 0);

				using (var data = new DataFactory())
					data.AddNewPhoto(new Photo() {
						Name = fileName, Notes = notes, Data = ms.ToArray(), CreatedOn = DateTime.Now
					});
			}

		}

		/// <summary>
		/// Uploads the photo.
		/// </summary>
		/// <param name="fileName">Name of the file.</param>
		/// <param name="notes">The notes.</param>
		/// <param name="bytes">The bytes.</param>
		/// <exception cref="System.NotImplementedException"></exception>
		[WebInvoke(UriTemplate = "UploadPhoto/{fileName}/{notes}", Method = "POST")]
		public void UploadPhoto(string fileName, string notes, Stream bytes) {
			var read = 0;
			var buffer = new byte[MaxBufferSize];

			using (var ms = new MemoryStream()) {
				do {
					read = bytes.Read(buffer, 0, buffer.Length);
					ms.Write(buffer, 0, read);
				} while (read > 0);

				using (var data = new DataFactory())
					data.AddNewPhoto(new Photo() {
						Name = fileName, Notes = notes, Data = ms.ToArray(), CreatedOn = DateTime.Now
					});
			}
		}

		/// <summary>
		/// Gets the first or last photo.
		/// </summary>
		/// <param name="sort">The sort.</param>
		/// <returns>Stream.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		[WebGet(UriTemplate = "GetLastPhoto/{sort}", BodyStyle = WebMessageBodyStyle.Bare)]
		public Stream GetFirstOrLastPhoto(string sort) {
			Photo selectedPhoto;
			MemoryStream retval = null;
			var sortVal = sort.Equals("Ascending", StringComparison.OrdinalIgnoreCase) ? Enums.SortOrder.Ascending : Enums.SortOrder.Descending;

			using (var data = new DataFactory()) {
				if ((selectedPhoto = data.GetFirstOrLastPhoto(sortVal)) != null) 
					retval = new MemoryStream(selectedPhoto.Data);
			}

			return retval;
		}

		/// <summary>
		/// Gets the photo by identifier.
		/// </summary>
		/// <param name="photoId">The photo identifier.</param>
		/// <returns>Stream.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		[WebGet(UriTemplate = "GetPhoto/{photoId}", BodyStyle = WebMessageBodyStyle.Bare)]
		public Stream GetPhotoById(string photoId) {
			Photo selectedPhoto;
			MemoryStream retval = null;
			using (var data = new DataFactory()) {
				if ((selectedPhoto = data.GetPhotoById(int.Parse(photoId))) != null)
					retval = new MemoryStream(selectedPhoto.Data);
			}

			return retval;
		}

		/// <summary>
		/// Gets the photo by identifier CPP.
		/// </summary>
		/// <returns>Stream.</returns>
		[WebGet(UriTemplate = "GetPhoto", BodyStyle = WebMessageBodyStyle.Bare)]
		public Stream GetPhotoByIdCpp() {
			Photo selectedPhoto;
			MemoryStream retval = null;

			var headers = WebOperationContext.Current.IncomingRequest.Headers;
			var photoId = int.Parse(headers["photoId"]);

			using (var data = new DataFactory()) {
				if ((selectedPhoto = data.GetPhotoById(photoId)) != null)
					retval = new MemoryStream(selectedPhoto.Data);
			}

			return retval;
		}

		/// <summary>
		/// Deletes the photo by identifier.
		/// </summary>
		/// <param name="photoId">The photo identifier.</param>
		[WebInvoke(UriTemplate = "DeletePhoto/{photoId}", Method = "DELETE")]
		public void DeletePhotoById(string photoId) {
			using (var data = new DataFactory())
				data.DeletePhotoById(int.Parse(photoId));
		}
	}
}