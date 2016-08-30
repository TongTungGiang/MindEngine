#include "NumberLeafCondition.h"
#include "IdCheck.h"

namespace RuleBased
{

template<typename T>
bool NumberLeafCondition<T>::matchesNode(DataNode *node, BindingList &bindings)
{
	if (!node->isLeaf())
		return false;

	bool idIsWildcard = IdCheck::isWildcard(name);
	if (!idIsWildcard &&
		name != node->getName())
		return false;

	LeafDataNode<T> *datum = (LeafDataNode<T>*)node;

	/**
	 * @todo Need adding bindings mechanism here
	 */
	if (min <= datum->getValue() && datum->getValue() <= max)
	{
		//if (idIsWildcard)
		{
			// Add to the binding list.
			bindings.push_back(node->getUniqueID());
		}
		return true;
	}

	return false;
}

template<typename T>
NumberLeafCondition<T>::NumberLeafCondition(NodeName name, T min, T max)
	: name(name), min(min), max(max), DataNodeCondition()
{
}

template<typename T>
RuleBased::NumberLeafCondition<T>::NumberLeafCondition(const char* name, T min, T max)
	: min(min), max(max), DataNodeCondition()
{
	this->name = NodeName(name);
}

template struct NumberLeafCondition<int>;
template struct NumberLeafCondition<float>;

}
