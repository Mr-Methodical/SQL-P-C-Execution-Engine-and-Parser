# SQL-P-C-Execution-Engine-and-Parser

## Links
- https://docs.aws.amazon.com/glue/latest/dg/catalog-and-crawler.html

## Notes
- Implemented path validation, reference lookup, and SQL JOIN rendering.
- Next: one-hop path resolution toward a native C++ engine with our own disk-backed B+ tree.

## Questions
- SQL-P has view based approaches that also make it easier to read. How is ours better/different from that?

## Schedule

aiming to have a small native C++ execution prototype working by **October 31**.

### This week: October 14–18

- Fix the empty-vector test so it fails properly if an invalid path is accepted.
- Add one-hop path resolution, connecting the existing reference lookup and JOIN rendering.
- Generate the complete SQL query for the AUTHOR/PAPER/WROTE example from C++ objects.
- Start representing joins and columns as structured data, with a small catalog for tables, column types, keys, and references.

### October 19–25

- Add in-memory tables and execute queries directly in C++.
- Implement scans, reference joins, equality filtering, projection, and DISTINCT.
- Test the example's results, empty matches, and duplicate removal before adding text parsing.

### October 26–31

- Add a parser for the small SQLP subset and connect it to the same execution plan.
- Test the full path from query text to results, including invalid input.
- Put together a reproducible demo and document what's supported.

### First prototype

The first version will use the AUTHOR/PAPER/WROTE fixture stored in memory. The scope is one FROM table, one projected path, direct columns or one reference hop, integer/string values, an optional equality filter, and SELECT DISTINCT. References will be explicit, valid, and non-null, pointing to unique keys.

The query I want to demonstrate is:

```sql
SELECT DISTINCT w.author.name AS author_name
FROM WROTE w
WHERE w.paper.title = 'Databases';
```

The expected result is Alice and Bob, with each appearing once and no guaranteed row order. The tests should also check empty results and reject unsupported syntax, unknown names, and type mismatches.

### Longer term

The next major goal is my own B+ tree integrated with the executor: first lookup, insertion, splits, and ranges in memory, then page-based storage, a bounded page cache, and a disk-backed tree. Persistence, deletion, transactions, crash recovery, and broader SQLP support will come after the first execution prototype.
