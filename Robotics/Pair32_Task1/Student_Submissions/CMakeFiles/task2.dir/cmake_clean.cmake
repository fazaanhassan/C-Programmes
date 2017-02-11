file(REMOVE_RECURSE
  "task2.pdb"
  "task2"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/task2.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
