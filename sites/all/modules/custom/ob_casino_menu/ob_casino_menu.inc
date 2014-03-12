<?php
/**
 * Page entity.
 */
class CasinoSpecialMenu extends Entity {
  protected function defaultUri() {
    return array('path' => 'casino-special-menu/' . $this->identifier());
  }
}

/**
 * Customization for EntityAPIController.
 */
class CasinoSpecialMenuController extends EntityAPIController {
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);
    field_attach_view('casino_special_menu', $entity, $view_mode, $langcode, array());
    return $build;
  }
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }
    $entity->updated = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }
}

/**
 * Customization for EntityAPIController.
 */
class CasinoSpecialMenuUIController extends EntityDefaultUIController {
  /**
   * Generates the table headers for the overview table.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    $header[] = array('data' => t('Meeting'));
    // Add operations with the right colspan.
    $header[] = array('data' => t('Operations'), 'colspan' => $this->operationCount());
    return $header;
  }

  /**
   * Generates the row for the passed entity and may be overridden in order to customize the rows.
   *
   * @param $additional_cols
   *   Additional columns to be added after the entity label column.
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }
    // Meeting
    $meeting = node_load($entity->meeting);
    $row[] = array('data' => $meeting->title ? $meeting->title : '');

    // Operations
    $row[] = l(t('edit'), $this->path . '/manage/' . $id);
    $row[] = l(t('Delete'), $this->path . '/manage/' . $id . '/delete');
    return $row;
  }
}

