<?php
/**
 * @file
 * Create and edit Casino Special Menu entity.
 */

/**
 * Page form.
 */
function casino_special_menu_form($form, &$form_state, $casino_special_menu = NULL) {
  $meeting_id = isset($_GET['meeting']) ? $_GET['meeting'] : NULL;
  $meetings = array();
  if (isset($casino_special_menu->is_new)) {
    if (!(user_access('create own meetings casino special menu') || user_access('create all meetings casino special menu'))) {
      drupal_access_denied();
      module_invoke_all('exit');
      exit();
    }
    $meetings = ob_cm_get_meetings(TRUE, TRUE);
    // if (user_access('create own meetings casino special menu')) {
    //   global $user;
    //   $node = node_load($meeting_id);
    //   if ($node->uid != $user->uid) {
    //     drupal_access_denied();
    //     module_invoke_all('exit');
    //     exit();
    //   }
    // }
  }
  else {
    if (!(user_access('edit own meetings casino special menu') || user_access('edit all meetings casino special menu'))) {
      drupal_access_denied();
      module_invoke_all('exit');
      exit();
    }
    $meetings = ob_cm_get_meetings(TRUE);
  }

  $form['meeting'] = array(
    '#type' => 'select',
    '#title' => t('Meeting'),
    '#default_value' => isset($casino_special_menu->meeting) ? $casino_special_menu->meeting : '',
    '#options' => $meetings,
    '#required' => TRUE,
  );
  if ($meeting_id) {
    $form['meeting']['#default_value'] = $meeting_id;
  } 
  if ((!isset($casino_special_menu->is_new)) || $meeting_id) {
    $form['meeting']['#type'] = 'hidden';
  }
  field_attach_form('casino_special_menu', $casino_special_menu, $form, $form_state);
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );
  $form['#submit'][] = 'casino_special_menu_form_submit';
  return $form;
}

/**
 * Submit handler for page entity form.
 */
function casino_special_menu_form_submit($form, &$form_state) {
  $casino_special_menu = entity_ui_form_submit_build_entity($form, $form_state);
  $casino_special_menu->save();
  drupal_set_message(t('Casino especial menu has been saved.'));
  $form_state['redirect'] = 'admin/casino-special-menu';
}