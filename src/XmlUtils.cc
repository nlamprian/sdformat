/*
 * Copyright 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <algorithm>

#include "XmlUtils.hh"

#include "sdf/Console.hh"

namespace sdf
{
inline namespace SDF_VERSION_NAMESPACE {

/////////////////////////////////////////////////
tinyxml2::XMLNode *DeepClone(tinyxml2::XMLDocument *_doc,
                              const tinyxml2::XMLNode *_src)
{
  if (_src == nullptr)
  {
    sdferr << "Pointer to XML node _src is NULL\n";
    return nullptr;
  }

  tinyxml2::XMLNode *copy = _src->ShallowClone(_doc);
  if (copy == nullptr)
  {
    sdferr << "Failed to clone node " << _src->Value() << "\n";
    return nullptr;
  }

  for (const tinyxml2::XMLNode *node = _src->FirstChild(); node != nullptr;
       node = node->NextSibling())
  {
    auto *childCopy = DeepClone(_doc, node);
    if (childCopy == nullptr)
    {
      sdferr << "Failed to clone child " << node->Value() << "\n";
      return nullptr;
    }
    copy->InsertEndChild(childCopy);
  }

  return copy;
}
}
}  // namespace sdf

