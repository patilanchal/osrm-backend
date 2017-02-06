#ifndef OSRM_PARTITION_RECURSIVE_BISECTION_STATE_HPP_
#define OSRM_PARTITION_RECURSIVE_BISECTION_STATE_HPP_

#include <cstddef>
#include <cstdint>
#include <vector>

#include "partition/bisection_graph.hpp"
#include "partition/graph_view.hpp"
#include "util/typedefs.hpp"

namespace osrm
{
namespace partition
{

// Keeps track of the bisection ids, modifies the graph accordingly, splitting it into a left/right
// section with consecutively labelled nodes. Requires a GraphView to look at.
class RecursiveBisectionState
{
  public:
    // The ID in the partition array
    using BisectionID = std::uint32_t;
    using NodeIterator = BisectionGraph::ConstNodeIterator;

    RecursiveBisectionState(BisectionGraph &bisection_graph);
    ~RecursiveBisectionState();

    BisectionID GetBisectionID(const NodeID node) const;

    // Bisects the node id array's sub-range based on the partition mask.
    // Returns: partition point of the bisection: iterator to the second group's first element.
    NodeIterator ApplyBisection(NodeIterator begin,
                                const NodeIterator end,
                                const std::size_t depth,
                                const std::vector<bool> &partition);

    // perform an initial pre-partitioning into small components
    // on larger graphs, SCCs give perfect cuts (think Amerika vs Europe)
    // This function performs an initial pre-partitioning using these sccs.
    std::vector<GraphView> PrePartitionWithSCC(const std::size_t small_component_size);

    const std::vector<BisectionID> &BisectionIDs() const;

  private:
    BisectionGraph &bisection_graph;
    std::vector<BisectionID> bisection_ids;
};

} // namespace partition
} // namespace osrm

#endif // OSRM_PARTITION_RECURSIVE_BISECTION_STATE_HPP_