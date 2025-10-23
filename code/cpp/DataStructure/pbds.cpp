// 자료형만 수정, less_equal <-> less 변경시 주의
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
// less_equal, greater_equal 사용시 필요
void m_erase(ordered_set &os, int val){
  int idx = osOS.order_of_key(val);
  ordered_set::iterator it = os.find_by_order(idx);
  if(*it == val) os.erase(it);
}