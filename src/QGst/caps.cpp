/*
    Copyright (C) 2009-2010  George Kiagiadakis <kiagiadakis.george@gmail.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "caps.h"
#include "structure.h"
#include "../QGlib/string_p.h"
#include <QtCore/QDebug>
#include <gst/gstcaps.h>
#include <gst/gstvalue.h>

namespace QGst {

//static
CapsPtr Caps::createSimple(const char *mediaType)
{
    return CapsPtr::wrap(gst_caps_new_simple(mediaType, NULL), false);
}

//static
CapsPtr Caps::createAny()
{
    return CapsPtr::wrap(gst_caps_new_any(), false);
}

//static
CapsPtr Caps::createEmpty()
{
    return CapsPtr::wrap(gst_caps_new_empty(), false);
}

//static
CapsPtr Caps::fromString(const char *string)
{
    return CapsPtr::wrap(gst_caps_from_string(string), false);
}

QString Caps::toString() const
{
    return QGlib::Private::stringFromGCharPtr(gst_caps_to_string(object<GstCaps>()));
}

//static
CapsPtr Caps::fromXml(xmlNodePtr node)
{
    return CapsPtr::wrap(gst_caps_load_thyself(node), false);
}

xmlNodePtr Caps::toXml(xmlNodePtr parent) const
{
    return gst_caps_save_thyself(object<GstCaps>(), parent);
}

void Caps::append(const CapsPtr & caps2)
{
    gst_caps_append(object<GstCaps>(), gst_caps_copy(caps2));
}

void Caps::merge(const CapsPtr & caps2)
{
    gst_caps_merge(object<GstCaps>(), gst_caps_copy(caps2));
}

void Caps::setValue(const char *field, const QGlib::Value & value)
{
    gst_caps_set_value(object<GstCaps>(), field, value);
}

bool Caps::simplify()
{
    return gst_caps_do_simplify(object<GstCaps>());
}

void Caps::truncate()
{
    gst_caps_truncate(object<GstCaps>());
}

SharedStructure Caps::structure(uint index)
{
    return SharedStructure(gst_caps_get_structure(object<GstCaps>(), index));
}

const SharedStructure Caps::structure(uint index) const
{
    return SharedStructure(gst_caps_get_structure(object<GstCaps>(), index));
}

void Caps::appendStructure(const StructureBase & structure)
{
    gst_caps_append_structure(object<GstCaps>(), gst_structure_copy(structure));
}

void Caps::mergeStructure(const StructureBase & structure)
{
    gst_caps_merge_structure(object<GstCaps>(), gst_structure_copy(structure));
}

void Caps::removeStructure(uint index)
{
    gst_caps_remove_structure(object<GstCaps>(), index);
}

uint Caps::size() const
{
   return gst_caps_get_size(object<GstCaps>());
}

bool Caps::isSimple() const
{
    return GST_CAPS_IS_SIMPLE(object<GstCaps>());
}

bool Caps::isAny() const
{
    return gst_caps_is_any(object<GstCaps>());
}

bool Caps::isEmpty() const
{
    return gst_caps_is_empty(object<GstCaps>());
}

bool Caps::isFixed() const
{
    return gst_caps_is_fixed(object<GstCaps>());
}

bool Caps::equals(const CapsPtr & caps2) const
{
    return gst_caps_is_equal(object<GstCaps>(), caps2);
}

bool Caps::isAlwaysCompatibleWith(const CapsPtr & caps2) const
{
    return gst_caps_is_always_compatible(object<GstCaps>(), caps2);
}

bool Caps::isSubsetOf(const CapsPtr & superset) const
{
    return gst_caps_is_subset(object<GstCaps>(), superset);
}

bool Caps::canIntersect(const CapsPtr & caps2) const
{
    return gst_caps_can_intersect(object<GstCaps>(), caps2);
}

CapsPtr Caps::getIntersection(const CapsPtr & caps2) const
{
    return CapsPtr::wrap(gst_caps_intersect(object<GstCaps>(), caps2), false);
}

CapsPtr Caps::getUnion(const CapsPtr & caps2) const
{
    return CapsPtr::wrap(gst_caps_union(object<GstCaps>(), caps2), false);
}

CapsPtr Caps::getNormal() const
{
    return CapsPtr::wrap(gst_caps_normalize(object<GstCaps>()), false);
}

CapsPtr Caps::subtract(const CapsPtr & subtrahend) const
{
    return CapsPtr::wrap(gst_caps_subtract(object<GstCaps>(), subtrahend), false);
}

CapsPtr Caps::copy() const
{
    return CapsPtr::wrap(gst_caps_copy(object<GstCaps>()), false);
}

CapsPtr Caps::copyNth(uint index) const
{
    return CapsPtr::wrap(gst_caps_copy_nth(object<GstCaps>(), index), false);
}

void Caps::ref()
{
    gst_caps_ref(GST_CAPS(m_object));
}

void Caps::unref()
{
    gst_caps_unref(GST_CAPS(m_object));
}

void Caps::makeWritable()
{
    m_object = gst_caps_make_writable(GST_CAPS(m_object));
}

} //namespace QGst

QGLIB_REGISTER_VALUEIMPL_IMPLEMENTATION(
    QGst::CapsPtr,
    QGst::CapsPtr::wrap(gst_caps_copy(gst_value_get_caps(value)), false),
    gst_value_set_caps(value, data)
)

QDebug operator<<(QDebug debug, const QGst::CapsPtr & caps)
{
    debug.nospace() << "QGst::Caps(" << caps->toString() << ")";
    return debug.space();
}