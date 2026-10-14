# SQL-P-C-Execution-Engine-and-Parser
- Goal Today:
One FROM table, paths following explicitly declared references, one equality filter, and literal-valued output columns. Use single-column keys, valid non-null references, and SELECT DISTINCT.

## Links
- https://docs.aws.amazon.com/glue/latest/dg/catalog-and-crawler.html

## Notes
- Implemented path validation, reference lookup, and SQL JOIN rendering.
- Next: one-hop path resolution toward a native C++ engine with our own disk-backed B+ tree.

## Questions
- SQL-P has view based approaches that also make it easier to read. How is ours better than that?
