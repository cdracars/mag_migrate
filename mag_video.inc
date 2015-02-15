<?php

/**
 * @file
 * Common mappings for the Drupal 6 node migrations.
 */

abstract class MagVideoNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $options = array('track_changes' => 1);
    $this->highwaterField = array();
    drush_print((string)$this->source);
    $this->addFieldMapping('field_legacy_nid', 'nid')
         ->description('We have a common field to save the D6 nid');
  }
}

class MagVideoItemMigration extends MagVideoNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addFieldMapping('field_section', '48')
      ->sourceMigration('article_type')
      ->arguments(array('source_type' => 'tid'));
    $this->addFieldMapping('field_video', 'field_embedded_video');
    $this->addFieldMapping('field_video:video_url', 'field_embedded_video:value');
    // Map the image field to the new image field,
    // base this on the Files migration.
    $this->addFieldMapping('field_image', 'field_op_video_thumbnail')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:source_dir')
      ->defaultValue('http://magazine.usao.edu/sites/default/files/');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(TRUE);
    // End image mapping.
    // This will set the text format.
    //$this->addFieldMapping('D7_COLUMN_NAME:format')
    //  ->defaultValue('filtered_html');
  }
}
