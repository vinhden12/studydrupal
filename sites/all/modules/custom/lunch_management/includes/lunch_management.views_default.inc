/**
 * Implementation of hook_views_default_views().
 */
function mymodule_views_default_views() {
 
  //PASTE EXPORTED VIEW CODE HERE
 
  $views[$view->name] = $view;
  return $views;
}
