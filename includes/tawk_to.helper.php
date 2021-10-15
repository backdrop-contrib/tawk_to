<?php
/**
 * @file
 * @package   tawk.to module for Backdrop CMS
 * @copyright (C) 2021 tawk.to
 * @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 */

class TawkHelper {
  const TAWK_TO_PAGE_ID = 'page_id';
  const TAWK_TO_WIDGET_ID = 'widget_id';
  const TAWK_TO_WIDGET_OPTIONS = 'widget_options';
  const TAWK_TO_WIDGET_USER_ID = 'widget_user_id';
  const TAWK_TO_CONFIG_NAME = 'tawk_to.settings';

	public static function get_widget() {
    $config_name = TawkHelper::TAWK_TO_CONFIG_NAME;
		return array(
			'page_id' => config_get($config_name, TawkHelper::TAWK_TO_PAGE_ID),
			'widget_id' => config_get($config_name,TawkHelper::TAWK_TO_WIDGET_ID),
		);
	}

	public static function check_same_user($current_user) {
		$saved_user = config_get(
      TawkHelper::TAWK_TO_CONFIG_NAME,
      TawkHelper::TAWK_TO_WIDGET_USER_ID
    );

		if (empty($saved_user)) {
			return false;
		}

		return $current_user === $saved_user;
	}

	/**
	 * Base url for tawk.to application which serves iframe.
	 */
	public static function get_base_url() {
		return 'https://plugins.talk.lv';
	}

	/**
	 * Constructs url for configuration iframe.
	 */
	public static function get_iframe_url() {
		$widget = TawkHelper::get_widget();

		if (!$widget) {
		$widget = array(
			'page_id'   => '',
			'widget_id' => '',
		);
		}
		return TawkHelper::get_base_url() . '/generic/widgets?currentWidgetId=' . $widget['widget_id'] . '&currentPageId=' . $widget['page_id'];
	}
}
