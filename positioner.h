#include <Windows.h>
#include "oopWin.h"
#include "UIStructs.h"
#include <set>
#include <string>
namespace BoolApp
{
	class Positionable
	{
	public:
		virtual void position() = 0;
	};
	void PositioningOne(pcomponent *comp){
		if (!comp->getContent())
		{
			return;
		}
		Size absolutParentSize = comp->getAbsoluteSize();
		Padding padding = comp->padding;
		padding = padding.toAbsolut(absolutParentSize);
		Point cord = (0, 0);
		padding.reRect(cord, absolutParentSize);

		Size absolutSize = comp->getContent()->size.toAbsolut(absolutParentSize);
		MarginType marginType = (comp->marginType & ~MarginType::PARENT) | (comp->getContent()->marginType & MarginType::PARENT);
		comp->getContent()->margin.toAbsolut(absolutParentSize).reRect(cord, absolutParentSize, absolutSize, marginType);
		comp->getContent()->Move(cord, absolutSize);
	}
	static void PositioningFew(pcomposite *compos)
	{
		Point cursor = (0, 0);
		Size size = compos->getAbsoluteSize();
		compos->padding.reRect(cursor, size);

		Size contSize = compos->GetContentSize(size);
		Margin tempMargin = Margin(0, 0, 0, 0);
		Point start = (0, 0);
		Size buffer = Size(size);
		tempMargin.reRect(start, buffer, contSize, compos->marginType);
		MarginType MBuffer = compos->marginType;

		Size contentSize = size;

		if (start.x < cursor.x)
		{
			MBuffer = (MarginType)(MBuffer ^ MarginType::HCENTER | MarginType::LEFT);
		}
		if (start.y < cursor.y)
		{
			MBuffer = (MarginType)(MBuffer ^ MarginType::VCENTER | MarginType::TOP);
		}
		cursor.y = start.y;
		cursor.x = start.x;
		for (int cont = 0; cont < compos->len(); cont++)
		{
			Margin amargin = compos->get(cont)->margin.toAbsolut(size);
			Size asize = compos->get(cont)->size.toAbsolut(size);
			Point cord = cursor;
			MarginType marginType = MBuffer & ~MarginType::PARENT | (compos->get(cont)->marginType & MarginType::PARENT);
			// amargin.reRect ( cord , contentSize , asize , marginType);
			cord.x += amargin.left;
			cord.y += amargin.top;
			compos->get(cont)->Move(cord, asize);
			if (compos->orientation)
			{
				if (marginType & MarginType::LEFT)
					contentSize = contentSize.minusBottom(asize, amargin);
				cursor.y += asize.height + amargin.top + amargin.bottom;
			}
			else
			{
				if (marginType & MarginType::TOP)
					contentSize = contentSize.minusRight(asize, amargin);
				cursor.x += asize.width + amargin.left + amargin.right;
			}
			contentSize = size;
		}
	}

	static void Positioning(ProcessView *pv)
	{
		Positionable *posit = dynamic_cast<Positionable *>(pv);
		if (posit)
		{
			posit->position();
		}
		else
		{
			pcomponent *comp = dynamic_cast<pcomponent *>(pv);
			if (comp)
			{
				PositioningOne(comp);
			}
			else
			{
				pcomposite *compos = dynamic_cast<pcomposite *>(pv);
				if (compos)
				{
					PositioningFew(compos);
				}
			}
		}
	}
}