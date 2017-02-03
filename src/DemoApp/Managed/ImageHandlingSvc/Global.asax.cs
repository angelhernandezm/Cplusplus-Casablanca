using System;
using System.Web;
using System.Web.Routing;
using System.ServiceModel.Activation;

namespace ImageHandlingSvc {
	public class Global : HttpApplication {

		/// <summary>
		/// Handles the Start event of the Application control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
		protected void Application_Start(object sender, EventArgs e) {
			RegisterRoutes();
		}

		/// <summary>
		/// Registers the routes.
		/// </summary>
		private void RegisterRoutes() {
			RouteTable.Routes.Add(new ServiceRoute("photos", new WebServiceHostFactory(), typeof(PhotoService)));
		}
	}
}