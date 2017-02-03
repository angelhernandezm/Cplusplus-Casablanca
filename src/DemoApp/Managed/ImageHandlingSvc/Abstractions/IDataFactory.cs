using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageHandlingSvc.Common;

namespace ImageHandlingSvc.Abstractions {
	public interface IDataFactory {
		/// <summary>
		/// Gets the photos.
		/// </summary>
		/// <returns>IList{Photo}.</returns>
		List<Photo> GetPhotos();

		/// <summary>
		/// Adds the new photo.
		/// </summary>
		/// <param name="photo">The photo.</param>
		void AddNewPhoto(Photo photo);

		/// <summary>
		/// Gets the first or last photo.
		/// </summary>
		/// <param name="order">The order.</param>
		/// <returns>Photo.</returns>
		Photo GetFirstOrLastPhoto(Enums.SortOrder order);

		/// <summary>
		/// Gets the photoby identifier.
		/// </summary>
		/// <param name="id">The identifier.</param>
		/// <returns>Photo.</returns>
		Photo GetPhotoById(int id);

		/// <summary>
		/// Deletes the photo by identifier.
		/// </summary>
		/// <param name="id">The identifier.</param>
		void DeletePhotoById(int id);
	}
}
