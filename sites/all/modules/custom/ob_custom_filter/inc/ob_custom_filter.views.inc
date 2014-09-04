<?php
/**
* Implementation of hook_views_handlers() to register all of the basic handlers
* views uses.
*/
function ob_custom_filter_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'ob_custom_filter') . '/inc', // path to view files
    ),
    'handlers' => array(
      // register our custom filter, with the class/file name and parent class
      'ob_custom_filters_filter_multiple' => array(
        'parent' => 'views_handler_filter',
      )
    ),
  );
}


function ob_custom_filter_views_data() {
  $data = array();
  
  // The flexible date filter.
  $data['node']['ob_custom_filter'] = array(
    'group' => t('Custom'),
    'real field'  => 'ob_custom_filter',
    'title' => t('Custom Date/Term combined filter'),
    'help' => t('Filter any Views based on date and term'),
    'filter' => array(
      'handler' => 'ob_custom_filters_filter_multiple'
    ),
  ); 
  
  return $data;
}