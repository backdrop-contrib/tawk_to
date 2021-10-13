<?php
/**
 * @file
 * @package   tawk.to module for Backdrop CMS
 * @copyright (C) 2021 tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

/**
 * tawk.to widget visibility options form.
 */
function tawk_to_visibility_opts_form($form, &$form_state) {
  $display_opts = config_get(TAWK_TO_CONFIG_NAME, TAWK_TO_WIDGET_OPTIONS);

  if ($display_opts && !empty($display_opts)) {
    $display_opts = json_decode($display_opts);
  }
  else {
    $display_opts = null;
  }

  // visibility settings
  $form['visibility_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility Settings'),
    '#description' => t('Define where the tawk.to widget will and won\'t show'),
  );

  // always display config
  $always_display_attr = array();
  if (!is_null($display_opts) && $display_opts->always_display) {
    $always_display_attr['checked'] = true;
  }

  $form['visibility_settings']['always_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always show Tawk.To widget on every page'),
    '#description' => t('Select to show on all except the exceptions
    De-select to select the specific pages'),
    '#id' => t('always_display'),
    '#attributes' => $always_display_attr,
  );

  // exclude url config
  $form['visibility_settings']['hide_oncustom'] = array(
    '#type' => 'textarea',
    '#title' => t('Except on pages:'),
    '#description' => t('Add URLs to pages in which you would like to hide the widget.<br>
    Put each URL in a new line and just include the leading \'/\' and page URL (e.g. /about)'),
    '#prefix' => '<div class="div_hide_specific">',
    '#suffix' => '</div>',
    '#id' => t('hide_oncustom'),
    '#default_value' => !is_null($display_opts) && $display_opts->hide_oncustom ?
      format_multiline_url_paths($display_opts->hide_oncustom) : '',
  );

  // show on front page config
  $show_onfrontpage_attr = array();
  if (!is_null($display_opts) && $display_opts->show_onfrontpage) {
    $show_onfrontpage_attr['checked'] = true;
  }

  $form['visibility_settings']['show_onfrontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on front page'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_onfrontpage'),
    '#attributes' => $show_onfrontpage_attr,
  );

  // show on taxonomy config
  $show_ontaxonomy_attr = array();
  if (!is_null($display_opts) && $display_opts->show_ontaxonomy) {
    $show_ontaxonomy_attr['checked'] = true;
  }

  $form['visibility_settings']['show_ontaxonomy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on taxonomy pages'),
    '#description' => t('Select to show on pages for taxonomy terms'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_ontaxonomy'),
    '#attributes' => $show_ontaxonomy_attr,
  );

  // include urls config
  $show_oncustom_default_value = '';
  if (!is_null($display_opts) && $display_opts->show_oncustom) {
    $show_oncustom_default_value = format_multiline_url_paths($display_opts->show_oncustom);
  }
  $form['visibility_settings']['show_oncustom'] = array(
    '#type' => 'textarea',
    '#title' => t('Show on pages:'),
    '#description' => t('Add URLs to pages in which you would like to show the widget.<br>
    Put each URL in a new line and just include the the leading \'/\' and page URL (e.g. /about)'),
    '#prefix' => '<div class="div_show_specific">',
    '#suffix' => '</div>',
    '#id' => t('show_oncustom'),
    '#default_value' =>  $show_oncustom_default_value,
  );

  // privacy settings
  $form['privacy_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Privacy Settings'),
    '#description' => t('Define whether or not user information can be used'),
  );

  // enable visitor recognition config
  $enable_visitor_recognition_attr = array();
  if (!is_null($display_opts) && $display_opts->enable_visitor_recognition) {
    $enable_visitor_recognition_attr['checked'] = true;
  }
  $form['privacy_settings']['enable_visitor_recognition'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable visitor recognition'),
    '#description' => t('If selected, name and email address from logged in users will be used to identify the user to you when a chat comes in via tawk.to'),
    '#id' => t('enable_visitor_recognition'),
    '#attributes' => $enable_visitor_recognition_attr,
  );

  // submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  $form['#submit'][] = 'tawk_to_visibility_opts_form_submit';

  return $form;
}

/**
 * tawk.to visibility options form submit handler
 */
function tawk_to_visibility_opts_form_submit($form, &$form_state) {
  $jsonOpts = array(
    'always_display' => false,
    'hide_oncustom' => array(),
    'show_onfrontpage' => false,
    'show_ontaxonomy' => false,
    'show_oncustom' => array(),
    'enable_visitor_recognition' => false,
  );

  $options = $form_state['values'];

  foreach ($options as $column => $value) {
    switch ($column) {
      case 'hide_oncustom':
      case 'show_oncustom':
        // replace newlines and returns with comma, and convert to array for saving
        $value = str_replace(["\r\n", "\r", "\n"], ',', $value);
        $value = explode(',', $value);
        $value = (empty($value)||!$value)?array():$value;
        $jsonOpts[$column] = json_encode($value);
        break;
      case 'show_onfrontpage':
      case 'show_ontaxonomy':
      case 'always_display':
      case 'enable_visitor_recognition':
        $jsonOpts[$column] = $value == 1;
        break;
    }
  }

  config_set(TAWK_TO_CONFIG_NAME, TAWK_TO_WIDGET_OPTIONS, json_encode($jsonOpts));

  // Flush page cache so widget options will update at next page load
  cache_flush('page');

  backdrop_set_message('Successfully set widget options to your site');
}

/**
 * Helper function to add new lines to url paths for displaying in textarea fields
 */
function format_multiline_url_paths($url_paths) {
  $paths = json_decode($url_paths);
  $formatted_paths = '';
  foreach($paths as $path) {
    if (!empty($formatted_paths)) {
      $formatted_paths .= "\r\n";
    }

    $formatted_paths .= $path;
  }
  return $formatted_paths;
}
