using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ImageHandlingSvc.Abstractions {
	public interface IPhoto {
		/// <summary>
		/// Gets or sets the photo identifier.
		/// </summary>
		/// <value>The photo identifier.</value>
		[DataMember]
		int PhotoId {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>The name.</value>
		[DataMember]
		string Name {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the notes.
		/// </summary>
		/// <value>The notes.</value>
		[DataMember]
		string Notes {
			get;
			set;
		}

		/// <summary>
		/// Gets or sets the created on.
		/// </summary>
		/// <value>The created on.</value>
		[DataMember]
		DateTime CreatedOn {
			get;
			set;
		}
	}
}
