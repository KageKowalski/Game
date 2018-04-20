namespace Utility {

		// Returns a unique unsigned int.
		unsigned int unique_id() {
		static unsigned int counter = 0;
		return counter++;
	}
}