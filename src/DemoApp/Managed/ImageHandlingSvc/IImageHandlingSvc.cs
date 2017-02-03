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

namespace ImageHandlingSvc {
	/// <summary>
	/// Interface IImageHandlingSvc
	/// </summary>
	[ServiceContract]
	public interface IImageHandlingSvc {
		/// <summary>
		/// Gets the photos.
		/// </summary>
		/// <returns>List{Photo}.</returns>
		[OperationContract]
		List<Photo> GetPhotos();

		/// <summary>
		/// Uploads the photo.
		/// </summary>
		/// <param name="fileName">Name of the file.</param>
		/// <param name="notes">The notes.</param>
		/// <param name="bytes">The bytes.</param>
		[OperationContract]
		void UploadPhoto(string fileName, string notes, Stream bytes);

		/// <summary>
		/// Uploads the photo.
		/// </summary>
		/// <param name="bytes">The bytes.</param>
		[OperationContract]
		void UploadPhotoCpp(Stream bytes);

		/// <summary>
		/// Gets the photo by identifier CPP.
		/// </summary>
		/// <returns>Stream.</returns>
		[OperationContract]
		Stream GetPhotoByIdCpp();

		/// <summary>
		/// Gets the first or last photo.
		/// </summary>
		/// <param name="sort">The sort.</param>
		/// <returns>Stream.</returns>
		[OperationContract]
		Stream GetFirstOrLastPhoto(string sort);

		/// <summary>
		/// Gets the photo by identifier.
		/// </summary>
		/// <param name="photoId">The photo identifier.</param>
		/// <returns>Stream.</returns>
		[OperationContract]
		Stream GetPhotoById(string photoId);

		/// <summary>
		/// Deletes the photo by identifier.
		/// </summary>
		/// <param name="photoId">The photo identifier.</param>
		[OperationContract]
		void DeletePhotoById(string photoId);

	}
}
