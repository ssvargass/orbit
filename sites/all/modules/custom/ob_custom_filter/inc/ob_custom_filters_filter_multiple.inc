<?php
class ob_custom_filters_filter_multiple extends views_handler_filter {
  
  /* this method is used to create the options form for the Views UI when creating a view
   * we use the standard drupal form api to return a form array, with the settings
   * we want to capture. 
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Step 1: fetch all our vocabularies, and build an array of options
    $terms = taxonomy_get_vocabularies();
    $show = array();
    foreach($terms as $term) {
      $show[$term->vid] = $term->name;
    }
    
    // Step 2: create a select field to choose Vocabulary options
    //   this allows you to choose which vocabulary to fetch terms for in the exposed filter
    $form['filter_vocab'] = array(
      '#type' => 'select',
      '#title'  => t('Vocabulary'),
      '#options'  => $show,
      '#default_value'  => $this->options['filter_vocab']
    );
    
    // Step 3: Create a checkbox field to select whether date options should be included
    $form['include_dates'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Include Date Filters'),
      '#default_value'  => $this->options['include_dates']
    );
  }
  
  /* I'll be perfectly honest, I have no idea if this is required or not. I *think* it may be
   * as it defines our filter field. However I don't use it. I added it when trying to get
   * things working...
   */
  function value_form(&$form, &$form_state) {
    $form['custom_filter']  = array(
      '#type' => 'textfield'
    );
  }
  
  /* A custom display for our exposed form. Views normally uses the value_form for this
   * however we're skipping that entirely since we want our exposed form to be a completely
   * different beast. It's entirely possible I could move this to value_form however...
   */
  function exposed_form(&$form, &$form_state) {
    // for my use case the filtering is controlled by javascript, which
    // submits the form and also handles a date select popup.
    drupal_add_js(drupal_get_path('module','custom_filter') . '/custom_filter.js');
    
    // if we're displaying date options, add them to the options for our output filter
    if ( $this->options['include_dates'] ) {
      $display = array(
        'all'               => t('Show all'),
        'last-four-weeks'   => t('Last four weeks'),
        'last-three-months' => t('Last three months'),
        'last-six-months'   => t('Last six months'),
        'last-year'         => t('Last year'),
        'advanced'          => t('Advanced'),
      );    
    } else {
      $display = array('all'  => t('Show all'));
    }
    
    // get the terms for our configured vocabulary and add them to the options
    // for my case, terms are only 1 level deep, will need changes
    // if you have nested terms.
    if ( $this->options['filter_vocab'] ) {
      $terms = taxonomy_get_tree($this->options['filter_vocab']);
      
      foreach( $terms as $term ) {
        $display[$term->tid] = $term->name;
      }
    }
    
    // now create our select element with the chosen options
    $form['custom_filter'] = array(
      '#type' => 'select',
      '#title'  => t('Browse By'),
      '#options'  => $display
    );
  }

  // the query method is responsible for actually running our exposed filter
  function query() {
    // make sure our base table is included in the query.
    // base table for this is node so it may be redundent...
    $this->ensure_my_table();

    // make sure term node is joined in if needed
    // not exactly optimal since we may not need it if we're filtering by date
    $this->query->add_table('term_node');
    
    // get the value of the submitted filter
    $value = $this->value[0];

    // a bit ugly. Since we have date and taxonomy options we need to do a switch to exhaust
    // the date options before we can assume it's a taxonomy term
    switch( $value ) {
      case 'all';
        return;
      case 'last-four-weeks':
        $this->query->add_where($this->options['group'], "node.created > %s", strtotime('4 weeks ago'));
        break;
      case 'last-three-months':
        $this->query->add_where($this->options['group'], "node.created > %s", strtotime('3 months ago'));
        break;
      case 'last-six-months':
        $this->query->add_where($this->options['group'], "node.created > %s", strtotime('6 months ago'));
        break;
      case 'last-year':
        $this->query->add_where($this->options['group'], "node.created > %s", strtotime('1 year ago'));
        break;
      default:
        if ( is_numeric($value) ) {
          $this->query->add_where($this->options['group'], "term_node.tid = %d", $value);
        }
    }
  }
}