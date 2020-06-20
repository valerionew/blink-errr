/*
 *
 * Project: BLINK-ERRR (github.com/valerionew/blink-errr)
 * File:   settings.h
 * Author: valerio\new (github.com/valerionew)
 *
 * Created on 24 march 2019, 21.15
 *
 * Target: ATtiny202 (0x1E 0x91 0x23)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */
void system_init();
void set_clock_1k();
void watchdog_enable();
void pit_enable();
void sleep();
