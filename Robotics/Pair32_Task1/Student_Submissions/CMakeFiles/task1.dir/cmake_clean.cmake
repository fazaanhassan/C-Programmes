file(REMOVE_RECURSE
  "task1.pdb"
  "task1"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/task1.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
