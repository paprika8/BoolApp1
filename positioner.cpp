#include "positioner.h"

namespace BoolApp
{
	void PositioningOne(PComponent *comp)
	{
		if (!comp->getPView())
		{
			return;
		}
		Size absolutParentSize = comp->getAbsoluteSize();
		Padding padding = comp->padding;
		padding = padding.toAbsolut(absolutParentSize);
		Point cord = (0, 0);
		padding.reRect(cord, absolutParentSize);

		Size absolutSize = comp->getPView()->size.toAbsolut(absolutParentSize);
		MarginType marginType = (comp->margin.type & ~MarginType::PARENT) | (comp->getPView()->margin.type & MarginType::PARENT);
		comp->getPView()->margin.toAbsolut(absolutParentSize).reRect(cord, absolutParentSize, absolutSize, marginType);
		comp->getPView()->Move(cord, absolutSize);
	}
	void PositioningFew(PComposite *compos)
	
	{
		Point cursor = (0, 0);
		Size size = compos->getAbsoluteSize();
		compos->padding.reRect(cursor, size);

		Size contSize = compos->GetContentSize(size);
		Margin tempMargin = Margin(0, 0, 0, 0);
		Point start = (0, 0);
		Size buffer = Size(size);
		tempMargin.reRect(start, buffer, contSize, compos->margin.type);
		MarginType MBuffer = compos->margin.type;

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
			Margin amargin = compos->getPView(cont)->margin.toAbsolut(size);
			Size asize = compos->getPView(cont)->size.toAbsolut(size);
			Point cord = cursor;
			MarginType marginType = MBuffer & ~MarginType::PARENT | (compos->getPView(cont)->margin.type & MarginType::PARENT);
			// amargin.reRect ( cord , contentSize , asize , marginType);
			cord.x += amargin.left;
			cord.y += amargin.top;
			compos->getPView(cont)->Move(cord, asize);
			if (compos->is_vert_orientation)
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
	void Positioning(ProcessView *pv)
	{
		Positionable *posit = dynamic_cast<Positionable *>(pv);
		if (posit)
		{
			posit->position();
		}
		else
		{
			PComponent *comp = dynamic_cast<PComponent*>(pv);
			if (comp)
			{
				PositioningOne(comp);
			}
			else
			{
				PComposite *compos = dynamic_cast<PComposite*>(pv);
				if (compos)
				{
					PositioningFew(compos);
				}
			}
		}
	}
}