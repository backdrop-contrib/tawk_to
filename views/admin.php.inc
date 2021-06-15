<?php
/**
* @file
* @package   tawk.to module for Backdrop CMS
* @copyright (C) 2021 tawk.to
* @license   GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
*/

/**
* Creates markup for settings page.
*/
function tawk_to_render_widget_iframe($base_url, $iframe_url, $widget=array(), $display_opts = null, $sameUser = true)
{   ob_start();
    ?><div id="content" >
        <div class="l-wrapper">
            <div class="l-wrapper-inner container container-fluid">
                <div class="l-messages" role="status" aria-label="Status messages" id="optionsSuccessMessage" style="display: none;">
                    <div class="messages status">
                        <h2 class="element-invisible">Status message</h2>
                        Successfully set widget options to your site
                    </div>
                </div>
                <div class="l-page-title">
                    <a id="main-content"></a>
                </div>
                <div class="l-content" role="main" aria-label="Main content">
                    <div>
                        <fieldset class="form-wrapper" id="property-widget-settings">
                            <legend><span class="fieldset-legend">Property and Widget Selection</span></legend>
                            <div class="fieldset-wrapper">
                                <div class="fieldset-description">Select the property and widget from your tawk.to account</div>
                                <?php if (!$sameUser) { ?>
                                    <div id="widget_already_set" class="alert alert-warning">Notice: Widget already set by other user</div>
                                <?php } ?>
                                <iframe id="tawkIframe" src="" style="min-height: 275px; width: 100%; border: none; margin: 5px 0;"></iframe>
                                <input type="hidden" class="hidden" name="page_id" value="<?php echo $widget['page_id']?>">
                                <input type="hidden" class="hidden" name="widget_id" value="<?php echo $widget['widget_id']?>">
                            </div>
                        </fieldset>
                        <form class="tawkto-widget-settings" action="" method="post" id="module_form" accept-charset="UTF-8">
                            <fieldset class="form-wrapper" id="visibility-settings">
                                <legend><span class="fieldset-legend">Visibility Settings</span></legend>
                                <div class="fieldset-wrapper">
                                    <div class="fieldset-description">Define where the Tawk.to widget will and won't show</div>
                                    <div class="form-item form-type-checkbox">
                                        <?php
                                            $checked = true;
                                            if (!is_null($display_opts)) {
                                                if (!$display_opts->always_display) {
                                                    $checked = false;
                                                }
                                            }
                                        ?>
                                        <input type="checkbox" id="always_display" name="always_display" value="1" class="checkbox" 
                                            <?php echo ($checked)?'checked':'';?> />
                                        <label class="option" for="always_display">Always show Tawk.To widget on every page</label>
										<div class="description">
                                            Select to show on all except the exceptions<br>
											De-select to select the specific pages
                                        </div>
                                    </div>
                                    <div class="form-item form-type-textarea div_hide_specific">
                                        <label for="hide_oncustom">Except on pages:</label>
                                        <div class="form-textarea-wrapper resizable textarea-processed resizable-textarea">
                                            <textarea class="form-textarea hide_specific" name="hide_oncustom" id="hide_oncustom" cols="40" rows="6"><?php if (!empty($display_opts->hide_oncustom)) {
                                                    $whitelist = json_decode($display_opts->hide_oncustom);                                                     
                                                    foreach ($whitelist as $page) { echo $page."\r\n"; }
                                            }?></textarea>
                                        </div>
                                        <div class="description">
                                            Add URLs to pages in which you would like to hide the widget.<br>
                                            Put each URL in a new line and just include the leading '/' and page URL (e.g. /about)
                                        </div>
                                    </div>
                                    <div class="form-item form-type-checkbox div_show_specific">
                                        <?php
                                            $checked = false;
                                            if (!is_null($display_opts)) {
                                                if ($display_opts->show_onfrontpage) {
                                                    $checked = true;
                                                }
                                            }
                                        ?>
                                        <input type="checkbox" id="show_onfrontpage" name="show_onfrontpage" value="1" class="checkbox show_specific" 
                                            <?php echo ($checked)?'checked':'';?> />
                                        <label class="option" for="show_onfrontpage">Show on front page</label>
                                    </div>
                                    <div class="form-item form-type-checkbox div_show_specific">
                                        <?php
                                            $checked = false;
                                            if (!is_null($display_opts)) {
                                                if ($display_opts->show_ontaxonomy) {
                                                    $checked = true;
                                                }
                                            }
                                        ?>
                                        <input type="checkbox" id="show_ontaxonomy" name="show_ontaxonomy" value="1" class="checkbox show_specific" 
                                            <?php echo ($checked)?'checked':'';?> />
                                        <label class="option" for="show_ontaxonomy">Show on taxonomy pages</label>
                                        <div class="description">
                                            Select to show on pages for taxonomy terms
                                        </div>										
                                    </div>
                                    <div class="form-item form-type-textarea div_show_specific">
                                        <label for="hide_oncustom">Show on pages:</label>
                                        <div class="form-textarea-wrapper resizable textarea-processed resizable-textarea">
                                            <textarea class="form-textarea show_specific" name="show_oncustom" id="show_oncustom" cols="40" rows="6"><?php if (isset($display_opts->show_oncustom) && !empty($display_opts->show_oncustom)) {
                                                $whitelist = json_decode($display_opts->show_oncustom);                                             
                                                foreach ($whitelist as $page) { echo $page."\r\n"; }
                                            }?></textarea>
											<div class="description">
                                                Add URLs to pages in which you would like to show the widget.<br>
                                                Put each URL in a new line and just include the the leading '/' and page URL (e.g. /about)
										    </div>
                                        </div>

                                    </div>                                              
                                </div>
                            </fieldset>
                            <fieldset class="form-wrapper" id="privacy-settings">
                                <legend><span class="fieldset-legend">Privacy Settings</span></legend>
                                <div class="fieldset-wrapper">
                                    <div class="fieldset-description">Define whether or not user information can be used</div>
                                    <div class="form-item form-type-checkbox">
                                        <?php
                                            $checked = 'checked';
                                            if (!is_null($display_opts) && !$display_opts->enable_visitor_recognition) {
                                                $checked = '';
                                            }
                                        ?>
                                        <input type="checkbox" class="checkbox" name="enable_visitor_recognition" id="enable_visitor_recognition" value="1"
                                            <?php echo $checked ?> />
                                        <label class="option" for="enable_visitor_recognition">Enable visitor recognition</label>
                                        <div class="description">
                                            If selected, name and email address from logged in users will be used to identify the user to you when a chat comes in via tawk.to
                                        </div>										
                                    </div>  
                                </div>
                            </fieldset>
                            <div class="form-actions" id="edit-actions">
                                <input class="button-primary form-submit" type="submit" id="module_form_submit_btn" name="submitBlockCategories" value="Save configuration">
                            </div>                      
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script type="text/javascript">
        var currentHost = window.location.protocol + "//" + window.location.host;
        var url = "<?php echo $iframe_url; ?>&pltf=drupal&pltfv=7&parentDomain=" + currentHost;
        jQuery("#tawkIframe").attr("src", url);
        var iframe = jQuery("#tawk_widget_customization")[0];
        window.addEventListener("message", function(e) {
            if(e.origin === "<?php echo $base_url; ?>") {
                if(e.data.action === "setWidget") {
                    setWidget(e);
                }

                if(e.data.action === "removeWidget") {
                removeWidget(e);
                }

                if(e.data.action === 'reloadHeight') {
                reloadIframeHeight(e.data.height);
                }
            }
        });

        function setWidget(e) {
            jQuery.post("/admin/config/tawk/setwidget", {
                pageId : e.data.pageId,
                widgetId : e.data.widgetId
                }, function(r) {
                if(r.success) {
                    $('input[name="page_id"]').val(e.data.pageId);
                    $('input[name="widget_id"]').val(e.data.widgetId);
                    $('#widget_already_set').hide();
                    e.source.postMessage({action: "setDone"}, "<?php echo $base_url; ?>");
                } else {
                    e.source.postMessage({action: "setFail"}, "<?php echo $base_url; ?>");
                }
            });
        }

        function removeWidget(e) {
            jQuery.post("/admin/config/tawk/removewidget", function(r) {
                if(r.success) {
                    $('input[name="page_id"]').val('');
                    $('input[name="widget_id"]').val('');
                    $('#widget_already_set').hide();
                    e.source.postMessage({action: "removeDone"}, "<?php echo $base_url; ?>");
                } else {
                    e.source.postMessage({action: "removeFail"}, "<?php echo $base_url; ?>");
                }
            });
        }

        function reloadIframeHeight(height) {
            if (!height) {
                return;
            }

            var iframe = jQuery('#tawkIframe');
            if (height === iframe.height()) {
                return;
            }

            iframe.height(height);
        }

        jQuery(document).ready(function() {
            if(jQuery("#always_display").prop("checked")){
                jQuery('.show_specific').prop('disabled', true);
                jQuery(".div_show_specific").hide();
            } else {
                jQuery('.hide_specific').prop('disabled', true);
                jQuery(".div_hide_specific").hide();
            }

            jQuery("#always_display").change(function() {
                if(this.checked){
                    jQuery('.hide_specific').prop('disabled', false);
                    jQuery('.show_specific').prop('disabled', true);
                    jQuery(".div_hide_specific").show();
                    jQuery(".div_show_specific").hide();
                } else {
                    jQuery('.hide_specific').prop('disabled', true);
                    jQuery('.show_specific').prop('disabled', false);
                    jQuery(".div_hide_specific").hide();
                    jQuery(".div_show_specific").show();
                }
            });

            // process the form
            jQuery('#module_form').submit(function(event) {
                $path = "/admin/config/tawk/setoptions";
                jQuery.post($path, {
                    action     : 'set_visibility',
                    ajax       : true,
                    page_id    : jQuery('input[name="page_id"]').val(),
                    widget_id  : jQuery('input[name="widget_id"]').val(),
                    options    : jQuery(this).serialize()
                }, function(r) {
                    if(r.success) {
                        document.body.scrollTop = 0; // For Safari
                        document.documentElement.scrollTop = 0; // For Chrome, Firefox, IE and Opera
                        jQuery('#optionsSuccessMessage').toggle().delay(10000).fadeOut();
                    }
                });

                // stop the form from submitting the normal way and refreshing the page
                event.preventDefault();
            });
        });
    </script>
<?php
    $markup = ob_get_contents();
    ob_end_clean();
    return $markup;
}