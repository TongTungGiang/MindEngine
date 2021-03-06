#ifndef PATTERNNODE_H
#define PATTERNNODE_H

#include "ReteNode.h"
#include "DataGroupCondition.h"

#include "tinyxml2.h"

#include <string>
#include <map>

/**
 * @brief Contains classes to represent Rule-based system's database,
 * which stores knowledge available to the AI agent as well as the
 * implementation of rules and the mechanism to match the rules
 * and the data in the database.
 */
namespace RuleBased
{

/**
 * @brief Represents pattern nodes (aka. alpha nodes) of the Rete network.
 * The database will be passed into these pattern nodes which transfer the
 * matched facts to join nodes to perform Boolean operations.
 * @see ReteNode
 * @see JoinNode
 */
class PatternNode : public ReteNode, public IHashedReteNode
{

public:

	/**
	 * @brief Construct a pattern node with a condition;
	 * @param condition The condition that is associated with the pattern node.
	 */
	PatternNode(DataGroupCondition* condition, size_t hashCode);

	/**
	 * @brief A pattern node is a node which performs tests to the database
	 * (aka. working memory) and passes down all matched facts. Pattern nodes
	 * are also referred as alpha nodes.
	 * @return true if this node is a pattern node.
	 */
	virtual bool isPatternNode() const;

    /**
     * @brief Add a successor node to current list.
     * @param node The node is being added as the successor node of this node.
     * @return true of the node is successfully added, otherwise return false.
     */
    virtual bool addSuccessorNode(ReteNode *node);

    void match(DataNode* database);

    /**
     * @brief Add new variable name to this pattern node. This function is called at constructing phase.
     */
    void addVariableName(std::string variable);

public:

	// Begin IHashedReteNode interface
	virtual size_t getHashCode();
	// End IHashedReteNode interface;

private:

	/**
	* @brief Default constructor.
	*/
	PatternNode();

    /**
     * @brief Find nodes to match, which are the nodes with same name with the condition.
     * @param database The input database.
     * @param outNodes An array contains all nodes with same name with the condition. This parameter is both input and output.
     */
    void findNodesToMatchInDatabase(DataNode* database, std::vector<DataNode*> &outNodes);

    void pushOutputToSuccessors();

private:

    /**
     * @brief The condition associated with this pattern node.
     * The matching process would be performed upon this condition.
     * @see DataNodeCondition
     */
    DataNodeCondition* condition;

    std::vector<DataNode*> nodesToMatch;

    VariableBindings variableBindings;

	size_t hashCode;

};

}

#endif // PATTERNNODE_H
