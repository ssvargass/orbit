<?php
/**
 * @file
 * Registers tables in views.
 */

/**
 * Implements hook_views_data().
 */
function ob_polls_reports_views_data() {
  $data = array(
    'users_polls_opinion_answers' => array(
      'table' => array(
        'group' => t('Users polls opinion answers'),
        'base' => array(
          'field' => 'id',
          'title' => t('Users polls opinion answers'),
          'help' => t('Users polls opinion answers.'),
        ),
        'join()' => array(
          'node' => array(
            'left_field' => 'nid', 
            'field' => 'nid',
          ),
          'users' => array(
            'left_field' => 'uid', 
            'field' => 'uid',
          ),
        ),
      ),
      'id' => array(
        'title' => t('Id'),
        'help' => t('Id'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'uid' => array(
        'title' => t('Uid'),
        'help' => t('Uid'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'base' => 'users',
          'base field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Related user'),
          'title' => t('Related user'),
          'help' => t('Adds the relevant user to the mix.'),
        ),
      ),
      'nid' => array(
        'title' => t('Nid'),
        'help' => t('Nid'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'base' => 'node',
          'base field' => 'nid',
          'handler' => 'views_handler_relationship',
          'label' => t('Related node'),
          'title' => t('Related node'),
          'help' => t('Adds the relevant node to the mix.'),
        ),
      ),
      'choice' => array(
        'title' => t('Choice'),
        'help' => t('Choice'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'answer' => array(
        'title' => t('Answer'),
        'help' => t('Answer'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
    ),
  );
  return $data;
}
