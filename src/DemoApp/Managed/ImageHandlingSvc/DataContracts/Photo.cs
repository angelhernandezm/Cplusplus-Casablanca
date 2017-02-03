using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ImageHandlingSvc.Abstractions;

namespace ImageHandlingSvc.DataContracts {
	public class Photo : IPhoto {
		/// <summary>
		/// Gets or sets the photo identifier.
		/// </summary>
		/// <value>The photo identifier.</value>
		public int PhotoId {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>The name.</value>
		public string Name {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the notes.
		/// </summary>
		/// <value>The notes.</value>
		public string Notes {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the created on.
		/// </summary>
		/// <value>The created on.</value>
		public DateTime CreatedOn {
			get;
			set;
		}
	}
}