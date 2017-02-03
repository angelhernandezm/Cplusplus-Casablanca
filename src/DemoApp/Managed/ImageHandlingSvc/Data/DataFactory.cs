using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Web;
using ImageHandlingSvc.Abstractions;
using ImageHandlingSvc.Common;

namespace ImageHandlingSvc.Data {
	public class DataFactory : IDisposable, IDataFactory {
		#region "IDataFactory Interface"
		/// <summary>
		/// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
		/// </summary>
		public void Dispose() {
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		#endregion


		#region "IDataFactory Interface"


		/// <summary>
		/// Gets the photos.
		/// </summary>
		/// <returns>IList{Photo}.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		public List<Photo> GetPhotos() {
			var retval = from z in Model.Photos
						 orderby z.CreatedOn
						 select z;

			return (retval.ToList());

		}

		/// <summary>
		/// Adds the new photo.
		/// </summary>
		/// <param name="photo">The photo.</param>
		/// <exception cref="System.NotImplementedException"></exception>
		public void AddNewPhoto(Photo photo) {
			Model.Photos.Add(photo);
			Model.SaveChanges();
		}

		/// <summary>
		/// Gets the first or last photo.
		/// </summary>
		/// <param name="order">The order.</param>
		/// <returns>Photo.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		public Photo GetFirstOrLastPhoto(Common.Enums.SortOrder order) {
			var retval = order == Enums.SortOrder.Descending
			? (from z in Model.Photos orderby z.CreatedOn descending select z).FirstOrDefault()
			: (from z in Model.Photos orderby z.CreatedOn ascending select z).FirstOrDefault();

			return retval;
		}

		/// <summary>
		/// Gets the photoby identifier.
		/// </summary>
		/// <param name="id">The identifier.</param>
		/// <returns>Photo.</returns>
		/// <exception cref="System.NotImplementedException"></exception>
		public Photo GetPhotoById(int id) {
			var retval = (from z in Model.Photos
						  where z.PhotoId == id
						  select z).FirstOrDefault();

			return retval;
		}

		/// <summary>
		/// Deletes the photo by identifier.
		/// </summary>
		/// <param name="id">The identifier.</param>
		/// <exception cref="System.NotImplementedException"></exception>
		public void DeletePhotoById(int id) {
			var photo = (from z in Model.Photos
						 where z.PhotoId == id
						 select z).FirstOrDefault();

			if (photo != null) {
				Model.Photos.Remove(photo);
				Model.SaveChanges();
			}
		}

		#endregion


		/// <summary>
		/// Gets a value indicating whether this instance is disposed.
		/// </summary>
		/// <value><c>true</c> if this instance is disposed; otherwise, <c>false</c>.</value>
		protected bool IsDisposed {
			get;
			private set;
		}

		/// <summary>
		/// Gets the model.
		/// </summary>
		/// <value>The model.</value>
		protected PhotoSvcEntities Model {
			get;
			private set;
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="DataFactory"/> class.
		/// </summary>
		public DataFactory() {
			Model = new PhotoSvcEntities();
		}

		/// <summary>
		/// Finalizes an instance of the <see cref="DataFactory"/> class.
		/// </summary>
		~DataFactory() {
			Dispose(false);
		}

		/// <summary>
		/// Releases unmanaged and - optionally - managed resources.
		/// </summary>
		/// <param name="isDisposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
		protected virtual void Dispose(bool isDisposing) {
			if (!IsDisposed && isDisposing) {
				Model.Dispose();
				IsDisposed = true;
			}
		}

	}
}