/*
 * InputType.h
 *
 *  Created on: 14 Dec 2015
 *      Author: hieu
 */

#pragma once

#include "PhraseBased/ReorderingConstraint.h"
#include "TypeDef.h"

namespace Moses2
{

class InputType
{
public:
  //////////////////////////////////////////////////////////////////////////////
  class XMLOption
  {
  public:
	std::string nodeName;
	size_t startPos, phraseSize;

	std::string translation;
	SCORE prob;

	XMLOption()
	:prob(0)
	{}

	void Debug(std::ostream &out, const System &system) const;

  };

  //////////////////////////////////////////////////////////////////////////////

  InputType(long translationId, MemPool &pool);
  virtual ~InputType();

  virtual void Init(const System &system, size_t size, int max_distortion);

  long GetTranslationId() const
  {
    return m_translationId;
  }

  ReorderingConstraint &GetReorderingConstraint()
  { return m_reorderingConstraint; }

  const ReorderingConstraint &GetReorderingConstraint() const
  { return m_reorderingConstraint; }

  const std::vector<const XMLOption*> &GetXMLOptions() const
  { return m_xmlOptions; }

  void AddXMLOption(const System &system, const XMLOption *xmlOption);

  //! Returns true if there were any XML tags parsed that at least partially covered the range passed
  bool XmlOverlap(size_t startPos, size_t endPos) const;

protected:
  long m_translationId; 	//< contiguous Id
  ReorderingConstraint m_reorderingConstraint; /**< limits on reordering specified either by "-mp" switch or xml tags */
  std::vector<const XMLOption*> m_xmlOptions;
  std::vector <bool> m_xmlCoverageMap;

};

} /* namespace Moses2 */

