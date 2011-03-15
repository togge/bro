#ifndef brodocobj_h
#define brodocobj_h

#include <cstdio>
#include <string>
#include <list>

#include "ID.h"

class BroDocObj {
public:
	/**
	 * BroDocObj constructor
	 * @param id a pointer to an identifier that is to be documented
	 * @param reST a reference to a pointer of a list of strings that
	 *        represent the reST documentation for the ID.  The pointer
	 *        will be set to 0 after this constructor finishes.
	 * @param is_fake whether the ID* is a dummy just for doc purposes
	 */
	BroDocObj(const ID* id, std::list<std::string>*& reST,
	          bool is_fake = false);

	/**
	 * BroDocObj destructor
	 * Deallocates the memory associated with the list of reST strings
	 */
	~BroDocObj();

	/**
	 * Writes the reST representation of this object which includes
	 * 1) Any "##" or "##<" stylized comments.
	 *    Anything after these style of comments is inserted as-is into
	 *    the reST document.
	 * 2) a reST friendly description of the ID
	 * @param The (already opened) file to write the reST to.
	 */
	void WriteReST(FILE* file) const;

	/**
	 * Check whether this documentation is part of the public API
	 * (The declaration was while in an export section).
	 * @return true if the ID was declared in an export section, else false
	 */
	bool IsPublicAPI() const { return broID->IsExport(); }

	/**
	 * Return whether this object has documentation (## comments)
	 * @return true if the ID has comments associated with it
	 */
	bool HasDocumentation() const { return reST_doc_strings &&
	                                reST_doc_strings->size() > 0; }

protected:
	std::list<std::string>* reST_doc_strings;
	const ID* broID;
	bool is_fake_id; /**< Whether the ID* is a dummy just for doc purposes */

private:
};

#endif
