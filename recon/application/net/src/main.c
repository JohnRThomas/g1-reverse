/* SPDX-License-Identifier: Apache-2.0 */

/*
 * The recovered network-core implementation is supplied by the generated
 * retained-source manifest.  This entry point exists only to make the image a
 * standalone Zephyr application while ownership/link-map integration is being
 * proved.  HCI-RPMsg and the SoftDevice Controller are selected through
 * prj.conf and their normal pinned NCS module integration.
 */
int main(void)
{
	return 0;
}
