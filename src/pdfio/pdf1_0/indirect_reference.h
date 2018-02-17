#pragma once

namespace pdfio
{
	
namespace pdf1_0
{
	/*! \brief PDF indirect reference object.*/
	class IndirectReference
	{
	public:
		/*! \brief Default constructor.*/
		IndirectReference() = default;
		/*! \brief Initializes indirect reference by objectNumber and generationNumber.*/
		inline IndirectReference(int objectNumber, int generationNumber)
		: objectNumber_(objectNumber)
		, generationNumber_(generationNumber)
		{
			
		}
		/*! \brief Returns object number as rvalue.*/
		inline const int &objectNumber() const
		{
			return objectNumber_;
		}
		/*! \brief Returns object number as lvalue.*/
		inline int &objectNumber()
		{
			return objectNumber_;
		}
		/*! \brief Returns generation number as rvalue.*/
		inline const int &generationNumber() const
		{
			return generationNumber_;
		}
		/*! \brief Returns generation number as lvalue.*/
		inline int &generationNumber()
		{
			return generationNumber_;
		}
		
	private:
		int objectNumber_ = 0;
		int generationNumber_ = 0;
	};
}

}