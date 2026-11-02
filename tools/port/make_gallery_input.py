#!/usr/bin/env python3
"""Write the native disc-1 course-zero firing smoke input.

Use PE2_SKIPINTRO=1, PSYZ_HEADLESS=1 and PE2_PAD_REPLAY=<output>.
This is a development input route, not a recording of the original emulator.
Progress must be checked from game state, not inferred from clean replay EOF.
"""
import argparse
import json
import tempfile
from pathlib import Path


def write_route(path: Path, frames: int, aim_cycle: int = 0, leave_booth: bool = False, leave_airlock: bool = False, enter_parking: bool = False, shop_purchase: bool = False, enter_akropolis: bool = False, enter_tower: bool = False, enter_square: bool = False, square_telephone: bool = False, square_stairs: bool = False, enter_patio: bool = False, patio_swat: bool = False, east_hall_key: bool = False, leave_east_hall: bool = False, enter_cafeteria: bool = False, cafeteria_combat: bool = False, cafeteria_follow_up: bool = False, return_after_cafeteria: bool = False, mist_report: bool = False, enter_hallway: bool = False, enter_fountain: bool = False, fountain_path: bool = False, fountain_protein: bool = False, enter_security_room: bool = False, security_rupert_monitor: bool = False, hallway_blue_key: bool = False, security_blue_unlock: bool = False, enter_forked_road: bool = False, enter_observatory: bool = False, equip_tonfa: bool = False, observatory_combat: bool = False, enter_promenade: bool = False, promenade_combat: bool = False, enter_sanctuary: bool = False, enter_roof_garden: bool = False, sanctuary_red_key: bool = False, roof_garden_pyrokinesis: bool = False, roof_garden_combat: bool = False, roof_garden_bomb: bool = False, roof_garden_healing: bool = False, healed_observatory_return: bool = False, healed_security_return: bool = False, security_red_unlock: bool = False, bridge_entry: bool = False) -> None:
    security_red_unlock = security_red_unlock or bridge_entry
    healed_security_return = healed_security_return or security_red_unlock
    healed_observatory_return = healed_observatory_return or healed_security_return
    roof_garden_healing = roof_garden_healing or healed_observatory_return
    roof_garden_bomb = roof_garden_bomb or roof_garden_healing
    roof_garden_combat = roof_garden_combat or roof_garden_bomb
    roof_garden_pyrokinesis = roof_garden_pyrokinesis or roof_garden_combat
    sanctuary_red_key = sanctuary_red_key or roof_garden_pyrokinesis
    enter_roof_garden = enter_roof_garden or sanctuary_red_key
    enter_sanctuary = enter_sanctuary or enter_roof_garden
    promenade_combat = promenade_combat or enter_sanctuary
    enter_promenade = enter_promenade or promenade_combat
    observatory_combat = observatory_combat or enter_promenade
    equip_tonfa = equip_tonfa or observatory_combat
    enter_observatory = enter_observatory or observatory_combat
    enter_forked_road = enter_forked_road or enter_observatory
    security_blue_unlock = security_blue_unlock or enter_forked_road or equip_tonfa
    hallway_blue_key = hallway_blue_key or security_blue_unlock
    enter_security_room = enter_security_room or security_rupert_monitor
    fountain_path = fountain_path or fountain_protein
    enter_fountain = enter_fountain or fountain_path
    enter_hallway = enter_hallway or enter_fountain or enter_security_room or hallway_blue_key
    mist_report = mist_report or enter_hallway
    return_after_cafeteria = return_after_cafeteria or mist_report
    cafeteria_follow_up = cafeteria_follow_up or return_after_cafeteria
    cafeteria_combat = cafeteria_combat or cafeteria_follow_up
    enter_cafeteria = enter_cafeteria or cafeteria_combat
    leave_east_hall = leave_east_hall or enter_cafeteria
    east_hall_key = east_hall_key or leave_east_hall
    patio_swat = patio_swat or east_hall_key
    enter_patio = enter_patio or patio_swat
    square_stairs = square_stairs or enter_patio
    square_telephone = square_telephone or square_stairs
    enter_square = enter_square or square_telephone
    enter_tower = enter_tower or enter_square
    enter_akropolis = enter_akropolis or enter_tower
    shop_purchase = shop_purchase or enter_akropolis
    enter_parking = enter_parking or shop_purchase
    with path.open("w", encoding="ascii", newline="\n") as out:
        out.write("PE2PAD 1\n")

        def sample(index: int, mask: int) -> None:
            reply = bytes((0, 0x41, (~mask) & 255, ((~mask) >> 8) & 255)) + bytes(30)
            out.write(f"{index} {reply.hex()}\n")

        for index in range(frames):
            mask = 0
            if 150 <= index < 1000:
                phase = ((2 * index - 300 + 1) // 20) % 6
                if phase == 0:
                    mask |= 0x0008  # Start, through the opening/title
                if phase == 3:
                    mask |= 0x4000  # Cross, menu confirm
            if index >= 1000 and index % 60 < 8:
                mask |= 0x4000  # Captions/menu confirm; layout A maps to reload
            aiming = not aim_cycle or index % aim_cycle >= 15
            if index >= 3500 and aiming:
                mask |= 0x8000  # Square: aim; optionally release to reacquire
                if index % 30 < 8:
                    mask |= 0x0800  # R1: primary fire
            sample(index, mask)
        if leave_booth or leave_airlock or enter_parking:
            # Lower the weapon, back away from the rail, turn toward the
            # decontamination door, approach it, then confirm the exit.
            index = frames
            for duration, mask in ((200, 0), (200, 0x40), (24, 0x20), (270, 0x10), (60, 0)):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1
            for tick in range(900):
                sample(index, 0x4000 if tick % 60 < 8 else 0)
                index += 1

        if leave_airlock or enter_parking:
            # Walk through the chamber and confirm its corridor-side door.
            for duration, mask in ((80, 0x10), (24, 0x20), (40, 0x10), (60, 0)):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1
            for tick in range(900):
                sample(index, 0x4000 if tick % 60 < 8 else 0)
                index += 1
            for tick in range(680):
                mask = 0x10 if tick < 80 else 0
                if tick % 30 < 8:
                    mask |= 0x4000
                sample(index, mask)
                index += 1

        if enter_parking:
            # The control-room story starts on this route. Start uses its
            # authored skip script; no game state is modified by this tool.
            segments = (
                (24, 0x20), (400, 0x10), (24, 0x80), (40, 0x10), (60, 0), (900, None),
                (200, 0x10), (24, 0x80), (70, 0x10), (60, 0), (900, None),
                (8, 0x08), (1000, 0), (80, 0x10), (24, 0x80), (50, 0x10), (60, 0), (900, None),
                (360, 0x10), (60, 0),
            )
            for duration, mask in segments:
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1

        if shop_purchase:
            # Approach Jodie, select Shop / Ammunition / Buckshot, confirm one
            # pack, leave the UI, finish her dialogue and return to parking.
            segments = (
                (48, 0x20), (140, 0x10), (24, 0x80), (48, 0x10), (60, 0), (1800, None),
                (30, 0x10), (60, 0), (1200, None),
                (32, 0x10), (60, 0), (1200, None),
                (100, 0x10), (60, 0), (600, None),
                (8, 0x2000), (40, 0), (8, 0x40), (40, 0), (8, 0x4000), (150, 0),
                (8, 0x4000), (60, 0), (8, 0x4000), (120, 0),
                (8, 0x4000), (120, 0), (8, 0x2000), (60, 0),
                (8, 0x2000), (60, 0), (8, 0x2000), (120, 0),
                (8, 0x4000), (600, 0), (8, 0x4000), (300, 0), (8, 0x4000), (300, 0),
            )
            for duration, mask in segments:
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1
            # Back away as dialogue ends, so later confirms cannot reopen it.
            for tick in range(1200):
                sample(index, 0x40 | (0x4000 if tick % 60 < 8 else 0))
                index += 1
            for duration, mask in ((60, 0), (48, 0x20), (60, 0), (900, None)):
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1

        if enter_akropolis:
            # Approach Pierce's car, allow the prompt to reveal, select Ready
            # (one row below Not yet), then continue the departure dialogue.
            segments = (
                (24, 0x20), (180, 0x10), (24, 0x80), (80, 0x10), (60, 0), (180, None),
                (24, 0x20), (180, 0x10), (60, 0), (120, None),
                (36, 0x10), (24, 0x80), (36, 0x10), (60, 0),
                (8, 0x4000), (600, 0), (8, 0x40), (30, 0), (8, 0x4000), (120, 0), (5000, None),
            )
            for duration, mask in segments:
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1

        if enter_tower:
            # Walk through the mandatory sergeant, wreck and entrance scenes.
            for duration, mask in (
                (300, 0x10), (60, 0), (2000, None),
                (100, 0x10), (60, 0), (3000, None),
                (550, 0x10), (60, 0), (3000, None),
                (300, 0x10), (60, 0), (5000, None),
            ):
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1

        if enter_square:
            for duration, mask in ((24, 0x80), (400, 0x10), (60, 0), (1200, None)):
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1

        if square_telephone:
            # Trigger the stranger's departure, approach the ringing phone,
            # face it, use its menu and finish the following dialogue.
            for duration, mask in (
                (500, 0x10), (60, 0), (4000, None),
                (250, 0x10), (24, 0x80), (80, 0x10), (60, 0), (3000, None),
                (24, 0x20), (60, 0), (2400, None),
            ):
                for tick in range(duration):
                    buttons = (0x4000 if tick % 60 < 8 else 0) if mask is None else mask
                    sample(index, buttons)
                    index += 1
            for tick in range(3000):
                sample(index, 0x40 | (0x4000 if tick % 60 < 8 else 0))
                index += 1
            for _ in range(60):
                sample(index, 0)
                index += 1

        if square_stairs:
            # Approach the lower left stair while moving and interacting.
            # Waiting at its collision boundary first leaves the facing quad
            # out of reach. Let the real climb and landing finish afterwards.
            for duration, mask, confirm in (
                (90, 0x10, False), (24, 0x20, False),
                (500, 0x2010, True), (60, 0, False), (1500, 0, True),
            ):
                for tick in range(duration):
                    buttons = mask | (0x4000 if confirm and tick % 60 < 8 else 0)
                    sample(index, buttons)
                    index += 1

        if enter_patio:
            # Walk into the authored automatic stair/warp chain, then wait for
            # arrival control to be released in the actual patio room.
            for duration, mask in ((300, 0x10), (6000, 0)):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if tick % 60 < 8 else 0))
                    index += 1

        if patio_swat:
            # Trigger the SWAT opening, fight the Stranger, then approach the
            # follow-up scene. Leave the nearby examine trigger after dialogue.
            for duration, mask, confirm in (
                (14, 0x20, False), (150, 0x10, False), (6000, 0, True),
                (240, 0x10, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1
            for tick in range(6000):
                mask = (0x8000 if tick % 180 >= 15 else 0) | (0x0800 if tick % 30 < 8 else 0)
                sample(index, mask)
                index += 1
            for duration, mask, confirm in (
                (60, 0, False), (220, 0x10, False), (8000, 0, True),
                (350, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if east_hall_key:
            # Return through the patio stairs, cross the square below its
            # central obstacle, enter the east hall and finish its opening.
            for duration, mask, confirm in (
                (39, 0x20, False), (450, 0x10, False), (60, 0, False),
                (16, 0x80, False), (140, 0x2010, True), (2200, 0, True),
                (120, 0x2010, True), (2000, 0, True),
                (210, 0x10, False), (24, 0x20, False), (570, 0x10, False),
                (24, 0x20, False), (90, 0x10, False), (24, 0x80, False),
                (60, 0, False), (1800, 0, True), (500, 0x10, True), (9000, 0, True),
                (350, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if leave_east_hall:
            for duration, mask, confirm in ((32, 0x20, False), (440, 0x10, False), (2000, 0, True)):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1


        if enter_cafeteria:
            # Return to the patio with the key, approach the cafeteria door,
            # then run up its sloping approach and confirm the opening choice.
            for duration, mask, confirm in (
                (24, 0x20, False), (120, 0x10, False), (24, 0x80, False),
                (610, 0x10, False), (24, 0x80, False), (500, 0x2010, True),
                (1600, 0, True), (300, 0x10, True), (6000, 0, True),
                (8, 0x20, False), (470, 0x10, False), (16, 0x80, False),
                (60, 0, False), (4500, 0, True),
                (250, 0x2010, True), (1000, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1



        if cafeteria_combat:
            # Approach the authored battle ribbon, allow the opening scene to
            # finish, then fire with periodic aim release and reload/confirm.
            for duration, mask in ((10, 0x80), (100, 0x2010), (6000, 0),
                                   (10, 0x80), (55, 0x2010)):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if tick % 60 < 8 else 0))
                    index += 1
            for tick in range(9000):
                mask = ((0x8000 if tick % 180 >= 15 else 0)
                        | (0x0800 if tick % 30 < 8 else 0)
                        | (0x4000 if tick % 60 < 8 else 0))
                sample(index, mask)
                index += 1



        if cafeteria_follow_up:
            # Lower the weapon at the corpse. Action 0 examines the creature;
            # action 2 elsewhere in the room only examines the dead SWAT member.
            for duration, confirm in ((120, False), (8000, True)):
                for tick in range(duration):
                    sample(index, 0x4000 if confirm and tick % 60 < 8 else 0)
                    index += 1



        if return_after_cafeteria:
            # Let the real ambush play, then retreat through both stair sections.
            # The original escape penalty costs 10 BP; both enemies stay alive.
            for duration, mask, confirm in (
                (155, 0x2010, False), (350, 0, True),
                (53, 0x20, False), (165, 0x2010, False), (16, 0x80, False),
                (140, 0x2010, True), (2200, 0, True),
                (120, 0x2010, True), (2000, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1



        if mist_report:
            # Cross below the square's obstacle, report the new creature, close
            # the phone prompt and back away while still facing the phone.
            for duration, mask, confirm in (
                (210, 0x10, False), (24, 0x20, False), (570, 0x10, False),
                (8000, 0, True), (3000, 0x40, True), (60, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1



        if enter_hallway:
            # Clear the square's obstacle before climbing. Leave the returned
            # patio promptly, cross the cafeteria and use its north hallway door.
            for duration, mask, confirm in (
                (22, 0x20, False), (40, 0x10, False), (22, 0x80, False),
                (90, 0x10, False), (24, 0x20, False), (500, 0x2010, True),
                (60, 0, False), (1500, 0, True), (300, 0x10, True), (1000, 0, True),
                (8, 0x20, False), (470, 0x10, False), (16, 0x80, False),
                (250, 0x2010, True), (1500, 0, True),
                (500, 0x2010, False), (24, 0x80, False),
                (180, 0x10, True), (2000, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if enter_fountain:
            for duration, mask in ((180, 0x2010), (2000, 0)):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if tick % 60 < 8 else 0))
                    index += 1

        if fountain_path:
            # Examine the red-leaved tree, approach its replacement interaction
            # and finish the actual single-step ascent and scripted walk.
            for duration, mask, confirm in (
                (390, 0x10, False), (20, 0x20, False), (4000, 0, True),
                (100, 0x2010, True), (3000, 0, True),
                (20, 0x80, False), (55, 0x10, False), (24, 0x20, False), (3500, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if fountain_protein:
            # Inspect the upper medical case, take its Protein Capsule and
            # back away so the completed examination does not reopen.
            for duration, mask, confirm in (
                (13, 0x20, False), (50, 0x10, False), (23, 0x80, False),
                (50, 0x10, False), (5000, 0, True), (350, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if enter_security_room:
            # Branch from the hallway, run east and turn toward the security door.
            for duration, mask, confirm in (
                (145, 0x2010, False), (23, 0x80, False),
                (100, 0x2010, True), (1800, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if security_rupert_monitor:
            # Approach the console, brighten its picture, select camera 10,
            # finish Rupert's actual playback and close the monitor panel.
            for duration, mask, confirm in (
                (100, 0x2010, True), (2000, 0, True),
                (50, 0x10, True), (1800, 0, True),
                (23, 0x80, False), (24, 0x10, False), (23, 0x20, False),
                (90, 0x10, True), (1400, 0, True),
                (70, 0x80, False), (24, 0x10, False), (1800, 0, True),
                (78, 0x20, False), (82, 0x40, False), (4000, 0, True),
                (20, 0x2000, False), (240, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if hallway_blue_key:
            # Examine the key box, accept its Blue Key, and leave the prompt.
            for duration, mask, confirm in (
                (110, 0x2010, False), (23, 0x20, False), (100, 0x10, True),
                (4000, 0, True), (350, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if security_blue_unlock:
            # Enter security, open power supply, select the left lock's Item
            # command and use the first collected key through the actual menu.
            for duration, mask, confirm in (
                (23, 0x80, False), (40, 0x2010, False), (23, 0x80, False),
                (60, 0x2010, True), (1800, 0, True),
                (85, 0x2010, False), (23, 0x20, False), (30, 0x10, True),
                (1800, 0, True), (28, 0x80, False), (32, 0x40, False),
                (8, 0x4000, False), (240, 0, False), (8, 0x40, False),
                (24, 0, False), (8, 0x4000, False), (300, 0, False),
                (6000, 0, True), (20, 0x2000, False), (240, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if equip_tonfa:
            # Equip the carried Tonfa outside battle through Use / Weapon.
            for duration, mask in (
                (8, 0x8), (300, 0), (8, 0x4000), (240, 0),
                (8, 0x4000), (240, 0), (8, 0x4000), (300, 0),
                (8, 0x4000), (300, 0), (8, 0x8), (1000, 0),
            ):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1

        if enter_forked_road:
            # Return to the hallway, enter Fountain from its west door, follow
            # the upper path east, then run south along the outer corridor.
            for duration, mask, confirm in (
                (23, 0x20, False), (100, 0x2010, True), (1800, 0, True),
                (45, 0x2010, False), (23, 0x80, False),
                (45, 0x2010, True), (1800, 0, True),
                (260, 0x2010, False), (23, 0x80, False),
                (250, 0x2010, True), (1800, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if enter_observatory:
            # Cross the forked road, approach the escalator from its south
            # side, and finish both original outbound/arrival movie paths.
            for duration, mask, confirm in (
                (130, 0x2010, False), (23, 0x20, False),
                (145, 0x2010, False), (120, 0, False),
                (22, 0x80, False), (50, 0x2010, False), (23, 0x20, False),
                (100, 0x2010, True), (4000, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if observatory_combat:
            # Use the attached Recovery 2 from the battle Start menu, then
            # defeat both Grinning Strangers with the actual Tonfa attacks.
            for duration, mask, confirm in (
                (8, 0x8, False), (300, 0, False), (8, 0x20, False),
                (24, 0, False), (8, 0x20, False), (24, 0, False),
                (8, 0x4000, False), (600, 0, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1
            for tick in range(4000):
                sample(index, (0x8000 if tick % 180 >= 15 else 0) | (0x0800 if tick % 30 < 8 else 0))
                index += 1
            for _ in range(240):
                sample(index, 0)
                index += 1

        if enter_promenade:
            # Cross to the north escalator and finish the Promenade arrival.
            for duration, mask, confirm in (
                (46, 0x20, False), (90, 0x2010, False), (23, 0x20, False),
                (65, 0x2010, False), (23, 0x20, False),
                (60, 0x2010, True), (2000, 0, True),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if promenade_combat:
            # Approach the Mossbacks, defeat both with Tonfa and release aim.
            for duration, mask in ((23, 0x80), (200, 0x2010)):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1
            for tick in range(5000):
                sample(index, (0x8000 if tick % 180 >= 15 else 0) | (0x0800 if tick % 30 < 8 else 0))
                index += 1
            for _ in range(240):
                sample(index, 0)
                index += 1

        if enter_sanctuary:
            # Enter Sanctuary, finish its original No. 9/Rupert scene, then
            # back away from Rupert's repeatable doorway interaction.
            for duration, mask, confirm in (
                (22, 0x80, False), (80, 0x10, False), (23, 0x20, False),
                (75, 0x2010, True), (3500, 0, True), (8000, 0, True),
                (350, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if enter_roof_garden:
            # Follow the outer aisle around the pews, finish Sanctuary's bomb
            # scene and Roof Garden's arrival. Rupert then leaves Sanctuary.
            for duration, mask, confirm in (
                (23, 0x20, False), (170, 0x2010, False), (23, 0x80, False),
                (155, 0x2010, False), (23, 0x20, False),
                (6000, 0, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if sanctuary_red_key:
            # Return after Rupert leaves, approach the key via the west aisle,
            # accept the pickup dialog, and release scripted presentation.
            for duration, mask, confirm in (
                (37, 0x20, False), (60, 0x2010, True), (2000, 0, True), (120, 0, False),
                (23, 0x20, False), (60, 0x2010, False), (23, 0x80, False),
                (110, 0x2010, False), (23, 0x80, False), (75, 0x2010, True),
                (40, 0x10, True), (4000, 0, True), (350, 0x40, True), (120, 0, False),
                (120, 0, False), (8, 0x10, False), (24, 0, False),
                (8, 0x4000, False), (1000, 0, False), (200, 0x40, False), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if roof_garden_pyrokinesis:
            # Return through Sanctuary's outer aisle with the Red Key.
            for duration, mask, confirm in (
                (23, 0x80, False), (115, 0x2010, False), (23, 0x20, False),
                (42, 0x2010, False), (23, 0x80, False), (40, 0x2010, True),
                (2000, 0, True), (120, 0, False),
                (2, 0x20, False), (300, 0x2010, True), (2000, 0, True), (120, 0, False),
                (24, 0x80, False), (70, 0x2010, False), (23, 0x20, False),
                (250, 0x2010, False), (23, 0x20, False), (53, 0x2010, False),
                (23, 0x80, False), (60, 0x2010, True), (2000, 0, True), (120, 0, False),
                # Cross Roof Garden's bend, arm the drop and turn back through it.
                (60, 0x2010, False), (12, 0x20, False), (45, 0x2010, False),
                (11, 0x20, False), (50, 0x2010, False), (23, 0x80, False),
                (75, 0x10, False), (90, 0x40, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1
            for tick in range(800):
                sample(index, (0x8000 if tick % 180 >= 15 else 0) | (0x0800 if tick % 30 < 8 else 0))
                index += 1
            # One Tonfa kill, then open the real P.E. wheel and cast Pyrokinesis.
            for duration, mask in ((120, 0), (8, 0x1000), (180, 0), (8, 0x4000), (0 if roof_garden_combat else 180, 0)):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1

        if roof_garden_combat:
            # Resume Tonfa attacks immediately after the cast, then release aim.
            for tick in range(4000):
                sample(index, (0x8000 if tick % 180 >= 15 else 0) | (0x0800 if tick % 30 < 8 else 0))
                index += 1
            for _ in range(240):
                sample(index, 0)
                index += 1

        if roof_garden_bomb:
            # Reach the front of the bomb, complete its CAP dialogue and retreat
            # while confirming so the repeatable examine trigger cannot hold Aya.
            for duration, mask, confirm in (
                (14, 0x80, False), (40, 0x2010, False), (23, 0x80, False),
                (60, 0x10, False), (23, 0x80, False), (40, 0x10, True),
                (4000, 0, True), (200, 0x40, False), (120, 0, False),
                (120, 0x10, True), (4000, 0, True), (20, 0x40, False), (120, 0, False),
                (1000, 0x40, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1

        if roof_garden_healing:
            # Main menu -> P.E. -> Water -> Healing -> Revive -> Yes.
            for duration, mask in (
                (8, 0x8), (300, 0), (8, 0x40), (24, 0), (8, 0x40), (24, 0),
                (8, 0x4000), (300, 0), (8, 0x20), (120, 0), (8, 0x40), (24, 0),
                (8, 0x4000), (180, 0), (8, 0x4000), (180, 0), (8, 0x4000), (500, 0),
                # Close inventory, open the P.E. wheel (Healing is selected
                # outside battle) and cast with the game's ordinary controls.
                (8, 0x8), (1000, 0), (8, 0x1000), (180, 0), (8, 0x4000),
                (1000, 0), (120, 0),
            ):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1


        if healed_observatory_return:
            # Recorded return with Healing learned and Red Key retained.
            # Includes the original Roof Garden alignment attempts so sample
            # indices and the validated input prefix remain unchanged.
            for duration, mask, confirm in (
                (25, 0x10, False), (23, 0x80, False), (30, 0x2010, False),
                (23, 0x20, False), (80, 0x2010, False), (23, 0x20, False),
                (65, 0x10, False), (23, 0x80, False), (60, 0x2010, False),
                (23, 0x20, False), (80, 0x2010, False), (23, 0x80, False),
                (100, 0x2010, True), (2000, 0, True), (120, 0, False),
                (27, 0x20, False), (200, 0x2010, False), (240, 0, False),
                (46, 0x20, False), (15, 0x10, False), (24, 0x20, False),
                (250, 0x2010, True), (2000, 0, True), (120, 0, False),
                # Sanctuary -> Promenade.
                (40, 0x40, False), (23, 0x20, False), (80, 0x2010, False),
                (240, 0, False), (23, 0x80, False), (110, 0x2010, False),
                (240, 0, False), (23, 0x20, False), (60, 0x2010, True),
                (2000, 0, True), (120, 0, False),
                # Promenade -> Observatory, passing the live room enemies.
                (40, 0x2010, False), (240, 0, False), (23, 0x20, False),
                (600, 0x2010, False), (240, 0, False), (23, 0x20, False),
                (100, 0x2010, True), (2000, 0, True), (120, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1


        if healed_security_return:
            # Exact recorded return: Observatory/Forked Road escape panels,
            # Fountain Protein pickup, Hallway Healing cast and Security entry.
            # Keep alignment and interaction attempts to preserve the validated
            # prefix; these are ordinary controller inputs, not state restores.
            for duration, mask in (
                (23, 0x80), (600, 0x2010), (240, 0x0), (23, 0x20),
                (60, 0x2010), (240, 0x0), (23, 0x80), (230, 0x2010),
                (240, 0x0), (3, 0x20), (90, 0x2010), (23, 0x20),
                (25, 0x2010), (23, 0x80), (40, 0x2010), (23, 0x80),
                (8, 0x6010), (37, 0x2010), (400, 0x0), (8, 0x4000),
                (240, 0x0), (23, 0x80), (40, 0x10), (23, 0x20),
                (140, 0x2010), (25, 0x80), (8, 0x6010), (52, 0x2010),
                (8, 0x6010), (52, 0x2010), (8, 0x4000), (400, 0x0),
                (8, 0x4000), (240, 0x0), (245, 0x2010), (23, 0x20),
                (200, 0x2010), (23, 0x80), (35, 0x2010), (22, 0x20),
                (8, 0x6010), (52, 0x2010), (8, 0x6010), (7, 0x2010),
                (740, 0x0), (8, 0x4040), (52, 0x40), (8, 0x4040),
                (52, 0x40), (8, 0x4040), (52, 0x40), (8, 0x4040),
                (52, 0x40), (8, 0x4040), (52, 0x40), (8, 0x4040),
                (52, 0x40), (8, 0x4040), (52, 0x40), (8, 0x4040),
                (52, 0x40), (8, 0x4040), (52, 0x40), (8, 0x4040),
                (52, 0x40), (24, 0x80), (35, 0x2010), (22, 0x20),
                (175, 0x2010), (22, 0x80), (30, 0x2010), (23, 0x20),
                (8, 0x6010), (17, 0x2010), (400, 0x0), (8, 0x4000),
                (400, 0x0), (16, 0x2010), (23, 0x20), (35, 0x2010),
                (8, 0x4000), (400, 0x0), (8, 0x8), (120, 0x0),
                (8, 0x8), (60, 0x0), (8, 0x1000), (60, 0x0),
                (8, 0x4000), (240, 0x0), (8, 0x1000), (120, 0x0),
                (4, 0x4000), (160, 0x0), (76, 0x20), (8, 0x2010),
                (8, 0x4000), (240, 0x0), (8, 0x4000), (240, 0x0),
            ):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1


        if security_red_unlock:
            # Reach the power supply, select its right lock and use Red Key.
            # Complete the authored unlock, then close the repeatable panel.
            for duration, mask, confirm in (
                (85, 0x2010, False), (23, 0x20, False), (8, 0x4010, False),
                (22, 0x10, False), (400, 0, False), (32, 0x20, False),
                (32, 0x40, False), (8, 0x4000, False), (240, 0, False),
                (8, 0x4000, False), (240, 0, False), (8, 0x4000, False),
                (300, 0, False), (8, 0x4000, False), (240, 0, False),
                (2400, 0, True), (120, 0, False), (20, 0x2000, False),
                (400, 0, False),
            ):
                for tick in range(duration):
                    sample(index, mask | (0x4000 if confirm and tick % 60 < 8 else 0))
                    index += 1


        if bridge_entry:
            # Exact recorded post-Red route, including both hold escapes,
            # Healing, Observatory bat victory/results and Promenade traversal.
            # Only executed samples are retained; unsent stdin commands are not.
            for duration, mask in (
                (23, 0x20), (70, 0x2010), (8, 0x4000), (160, 0x0),
                (10, 0x2010), (8, 0x4000), (200, 0x0), (20, 0x2010),
                (8, 0x4000), (200, 0x0), (45, 0x2010), (23, 0x20),
                (18, 0x2010), (8, 0x4000), (160, 0x0), (45, 0x80),
                (35, 0x2010), (8, 0x4000), (120, 0x0), (4, 0x4000),
                (4, 0x8000), (4, 0x4000), (4, 0x8000), (4, 0x4000),
                (4, 0x8000), (4, 0x4000), (4, 0x8000), (27, 0x20),
                (40, 0x2010), (8, 0x4000), (120, 0x0), (8, 0x4000),
                (240, 0x0), (260, 0x2010), (23, 0x80), (180, 0x2010),
                (13, 0x80), (100, 0x2010), (8, 0x4000), (120, 0x0),
                (8, 0x4000), (240, 0x0), (8, 0x1000), (180, 0x0),
                (4, 0x4000), (240, 0x0), (130, 0x2010), (23, 0x20),
                (205, 0x2010), (22, 0x80), (25, 0x2010), (23, 0x20),
                (25, 0x2010), (8, 0x4000), (160, 0x0), (8, 0x4000),
                (240, 0x0), (25, 0x2010), (23, 0x20), (160, 0x2010),
                (588, 0x0), (4, 0x4000), (4, 0x8000), (4, 0x4000),
                (4, 0x8000), (4, 0x4000), (4, 0x8000), (4, 0x4000),
                (4, 0x8000), (8, 0xC800), (8, 0x8800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (8, 0xC800), (22, 0x8000),
                (8, 0xC800), (22, 0x8000), (4, 0x4000), (4, 0x8000),
                (4, 0x4000), (4, 0x8000), (4, 0x4000), (4, 0x8000),
                (4, 0x4000), (84, 0x8000), (46, 0x80), (8, 0xC800),
                (22, 0x8000), (8, 0xC800), (22, 0x8000), (8, 0xC800),
                (22, 0x8000), (8, 0xC800), (22, 0x8000), (8, 0xC800),
                (22, 0x8000), (8, 0xC800), (22, 0x8000), (8, 0xC800),
                (22, 0x8000), (8, 0xC800), (22, 0x8000), (240, 0x0),
                (8, 0x4000), (240, 0x0), (8, 0x4000), (240, 0x0),
                (50, 0x80), (60, 0x2010), (23, 0x20), (140, 0x2010),
                (24, 0x20), (25, 0x2010), (8, 0x4000), (240, 0x0),
                (24, 0x80), (325, 0x2010), (24, 0x20), (65, 0x2010),
                (8, 0x4000), (160, 0x0), (8, 0x4000), (240, 0x0),
            ):
                for _ in range(duration):
                    sample(index, mask)
                    index += 1


def write_captured_route(path: Path, name: str) -> None:
    """Append captured input to the unchanged startup prefix after the SPU fixes."""
    route = json.loads((Path(__file__).parent / f"routes/{name}.json").read_text())
    with tempfile.TemporaryDirectory(prefix="pe2_route_") as directory:
        base = Path(directory) / "base.pad"
        if route.get("baseRoute") in ("audio_fixed_east_hall", "video_clock_airlock", "video_clock_akropolis", "video_clock_tower", "video_clock_patio", "video_clock_patio_clear", "video_clock_parthenon_key", "video_clock_cafeteria", "video_clock_cafeteria_clear", "video_clock_patio_ambush", "video_clock_mist_report", "video_clock_fountain", "video_clock_fountain_path"):
            write_captured_route(base, route["baseRoute"])
        elif route.get("baseRoute") == "leave_booth":
            write_route(base, 20000, 180, leave_booth=True)
        else:
            write_route(base, 20000, 180, enter_square=True)
        lines = base.read_text().splitlines(keepends=True)
    index = route["baseSamples"]
    if len(lines) <= index:
        raise ValueError("startup route is shorter than the captured prefix")
    with path.open("w", encoding="ascii", newline="\n") as out:
        out.writelines(lines[:index + 1])
        for block in route["blocks"]:
            for _ in range(block["repeat"]):
                for duration, mask in block["steps"]:
                    if duration < 1 or not 0 <= mask <= 0xFFFF:
                        raise ValueError("invalid recorded controller segment")
                    reply = bytes((0, 0x41, (~mask) & 255, ((~mask) >> 8) & 255)) + bytes(30)
                    for _ in range(duration):
                        out.write(f"{index} {reply.hex()}\n")
                        index += 1
    if index != route["totalSamples"]:
        raise ValueError("captured route length mismatch")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("output", type=Path)
    parser.add_argument("--audio-fixed-east-hall", action="store_true",
                        help="replay the captured route after the sound fixes through Patio to Parthenon Key")
    parser.add_argument("--audio-fixed-cafeteria", action="store_true",
                        help="continue the captured sound-fixed route with the key to Cafeteria")
    parser.add_argument("--video-clock-airlock", action="store_true",
                        help="cross both gallery airlocks after the SPU fixes; run with --clock video")
    parser.add_argument("--video-clock-akropolis", action="store_true",
                        help="continue through parking to Akropolis Plaza; run with --clock video")
    parser.add_argument("--video-clock-tower", action="store_true",
                        help="cross Plaza and enter West Elevator Hall; run with --clock video")
    parser.add_argument("--video-clock-patio", action="store_true",
                        help="finish Square telephone and climb to Patio; run with --clock video")
    parser.add_argument("--video-clock-patio-clear", action="store_true",
                        help="defeat Patio Stranger and finish follow-up; run with --clock video")
    parser.add_argument("--video-clock-parthenon-key", action="store_true",
                        help="return through Square and receive Parthenon Key; run with --clock video")
    parser.add_argument("--video-clock-cafeteria", action="store_true",
                        help="return with Parthenon Key and enter Cafeteria; run with --clock video")
    parser.add_argument("--video-clock-cafeteria-clear", action="store_true",
                        help="defeat Cafeteria boss and return to Patio; run with --clock video")
    parser.add_argument("--video-clock-patio-ambush", action="store_true",
                        help="defeat both post-Cafeteria Patio Strangers; run with --clock video")
    parser.add_argument("--video-clock-mist-report", action="store_true",
                        help="heal after ambush and report Cafeteria by phone; run with --clock video")
    parser.add_argument("--video-clock-fountain", action="store_true",
                        help="cross Cafeteria/Hallway and confirm escape into Fountain; run with --clock video")
    parser.add_argument("--video-clock-fountain-path", action="store_true",
                        help="equip Tonfa and climb hidden Fountain path; run with --clock video")
    parser.add_argument("--video-clock-fountain-protein", action="store_true",
                        help="take Protein Capsule on upper Fountain path; run with --clock video")
    parser.add_argument("--frames", type=int, default=12000)
    parser.add_argument("--aim-cycle", type=int, default=0,
                        help="release aim for 15 samples every N samples (0 holds continuously)")
    parser.add_argument("--leave-booth", action="store_true",
                        help="append the verified route through the first airlock door after course zero")
    parser.add_argument("--leave-airlock", action="store_true",
                        help="append the verified route through both doors to the outside corridor")
    parser.add_argument("--enter-parking", action="store_true",
                        help="continue through both doors, skip the control-room scene with Start, and walk into parking")
    parser.add_argument("--shop-purchase", action="store_true",
                        help="continue to Jodie, buy one Buckshot pack, finish dialogue and return to parking")
    parser.add_argument("--enter-akropolis", action="store_true",
                        help="continue after the purchase and select Ready to enter Akropolis plaza")
    parser.add_argument("--enter-tower", action="store_true",
                        help="continue through the plaza scenes into the west elevator hall")
    parser.add_argument("--enter-square", action="store_true",
                        help="leave the west elevator hall and enter the central square")
    parser.add_argument("--square-telephone", action="store_true",
                        help="continue into the square, trigger the stranger scene and finish the phone interaction")
    parser.add_argument("--square-stairs", action="store_true",
                        help="finish the phone call, climb the left stairs and wait on the upper landing")
    parser.add_argument("--enter-patio", action="store_true",
                        help="continue over the upper landing into the patio and finish arrival")
    parser.add_argument("--patio-swat", action="store_true",
                        help="finish patio opening, defeat the Stranger and complete the SWAT follow-up")
    parser.add_argument("--east-hall-key", action="store_true",
                        help="return after the patio fight and obtain the cafeteria key in the east hall")
    parser.add_argument("--leave-east-hall", action="store_true",
                        help="obtain the cafeteria key and return to the square")
    parser.add_argument("--enter-cafeteria", action="store_true",
                        help="return with the key, open the patio door and enter the cafeteria")
    parser.add_argument("--cafeteria-combat", action="store_true",
                        help="enter the cafeteria, finish the opening and fight the Stranger")
    parser.add_argument("--cafeteria-follow-up", action="store_true",
                        help="defeat the cafeteria Stranger, examine it and finish the return to the patio")
    parser.add_argument("--return-after-cafeteria", action="store_true",
                        help="finish the cafeteria, trigger the patio ambush and retreat to the square")
    parser.add_argument("--mist-report", action="store_true",
                        help="return from the cafeteria, report the creature to MIST and leave the phone")
    parser.add_argument("--enter-hallway", action="store_true",
                        help="return after reporting to MIST, cross the cafeteria and enter the hallway")
    parser.add_argument("--enter-fountain", action="store_true",
                        help="cross the hallway and enter the fountain")
    parser.add_argument("--fountain-path", action="store_true",
                        help="find the fountain's hidden path and complete its climb")
    parser.add_argument("--fountain-protein", action="store_true",
                        help="climb the hidden path, collect the Protein Capsule and leave its prompt")
    parser.add_argument("--enter-security-room", action="store_true",
                        help="cross the hallway and enter the security-monitor room")
    parser.add_argument("--security-rupert-monitor", action="store_true",
                        help="enter security, brighten the monitor, watch Rupert on camera 10 and close the panel")
    parser.add_argument("--hallway-blue-key", action="store_true",
                        help="enter the hallway, collect its Blue Key and leave the prompt")
    parser.add_argument("--security-blue-unlock", action="store_true",
                        help="collect the Blue Key, use it at security's left lock and finish unlocking the escalator")
    parser.add_argument("--enter-forked-road", action="store_true",
                        help="unlock the escalator, return through the hallway and fountain, and enter the forked road")
    parser.add_argument("--enter-observatory", action="store_true",
                        help="unlock the escalator, cross the forked road and finish the ride into the observatory")
    parser.add_argument("--equip-tonfa", action="store_true",
                        help="unlock the escalator and equip the carried Tonfa through security's safe-room inventory")
    parser.add_argument("--observatory-combat", action="store_true",
                        help="equip Tonfa, reach Observatory, use Recovery 2 and defeat both Grinning Strangers")
    parser.add_argument("--enter-promenade", action="store_true",
                        help="finish Observatory combat and ride north to the Promenade")
    parser.add_argument("--promenade-combat", action="store_true",
                        help="reach Promenade and defeat both Brute Mossbacks with Tonfa")
    parser.add_argument("--enter-sanctuary", action="store_true",
                        help="finish Promenade combat and Sanctuary's No. 9/Rupert arrival scene")
    parser.add_argument("--enter-roof-garden", action="store_true",
                        help="finish Sanctuary bomb dialogue and Roof Garden arrival; Rupert leaves Sanctuary")
    parser.add_argument("--sanctuary-red-key", action="store_true",
                        help="finish Roof Garden arrival, return after Rupert leaves and collect the Red Key")
    parser.add_argument("--roof-garden-pyrokinesis", action="store_true",
                        help="return with Red Key, trigger Roof Garden ambush, fight with Tonfa and cast Pyrokinesis once")
    parser.add_argument("--roof-garden-combat", action="store_true",
                        help="return with Red Key and defeat the Roof Garden encounter using Tonfa and Pyrokinesis")
    parser.add_argument("--roof-garden-bomb", action="store_true",
                        help="defeat Roof Garden enemies, examine the bomb and resume normal control")
    parser.add_argument("--roof-garden-healing", action="store_true",
                        help="finish Roof Garden, learn Healing 1 for 750 EXP and cast it outside battle")
    parser.add_argument("--healed-observatory-return", action="store_true",
                        help="learn and cast Healing, then return with Red Key through Sanctuary and Promenade")
    parser.add_argument("--healed-security-return", action="store_true",
                        help="return with Red Key to Security Room, including native Healing during Hallway combat")
    parser.add_argument("--security-red-unlock", action="store_true",
                        help="return with Red Key, release the right Security Room lock and restore normal control")
    parser.add_argument("--bridge-entry", action="store_true",
                        help="use Red Key, clear the Observatory bat ambush and enter Bridge through Promenade")
    args = parser.parse_args()
    captured = [name for name in ("audio_fixed_east_hall", "audio_fixed_cafeteria", "video_clock_airlock", "video_clock_akropolis", "video_clock_tower", "video_clock_patio", "video_clock_patio_clear", "video_clock_parthenon_key", "video_clock_cafeteria", "video_clock_cafeteria_clear", "video_clock_patio_ambush", "video_clock_mist_report", "video_clock_fountain", "video_clock_fountain_path", "video_clock_fountain_protein") if getattr(args, name)]
    if captured:
        if len(captured) != 1 or any(value is True for name, value in vars(args).items() if name != captured[0]):
            parser.error("select one captured route without legacy progression flags")
        if args.frames != 20000 or args.aim_cycle != 180:
            parser.error("the captured route requires --frames 20000 --aim-cycle 180")
        write_captured_route(args.output, captured[0])
        return
    if (args.hallway_blue_key or args.security_blue_unlock or args.enter_forked_road or args.enter_observatory or args.equip_tonfa or args.observatory_combat or args.enter_promenade or args.promenade_combat or args.enter_sanctuary or args.enter_roof_garden or args.sanctuary_red_key or args.roof_garden_pyrokinesis or args.roof_garden_combat or args.roof_garden_bomb or args.roof_garden_healing or args.healed_observatory_return or args.healed_security_return or args.security_red_unlock or args.bridge_entry) and (args.enter_fountain or args.fountain_path or args.fountain_protein or args.enter_security_room or args.security_rupert_monitor):
        parser.error("blue-key progression is a separate route from the hallway")
    if (args.enter_security_room or args.security_rupert_monitor) and (args.enter_fountain or args.fountain_path or args.fountain_protein):
        parser.error("security room and fountain are separate routes from the hallway")
    if args.frames < 1:
        parser.error("--frames must be positive")
    if args.aim_cycle and args.aim_cycle < 60:
        parser.error("--aim-cycle must be zero or at least 60")
    if (args.leave_booth or args.leave_airlock or args.enter_parking or args.shop_purchase or args.enter_akropolis or args.enter_tower or args.enter_square or args.square_telephone or args.square_stairs or args.enter_patio or args.patio_swat or args.east_hall_key or args.leave_east_hall or args.enter_cafeteria or args.cafeteria_combat or args.cafeteria_follow_up or args.return_after_cafeteria or args.mist_report or args.enter_hallway or args.enter_fountain or args.fountain_path or args.fountain_protein or args.enter_security_room or args.security_rupert_monitor or args.hallway_blue_key or args.security_blue_unlock or args.enter_forked_road or args.enter_observatory or args.equip_tonfa or args.observatory_combat or args.enter_promenade or args.promenade_combat or args.enter_sanctuary or args.enter_roof_garden or args.sanctuary_red_key or args.roof_garden_pyrokinesis or args.roof_garden_combat or args.roof_garden_bomb or args.roof_garden_healing or args.healed_observatory_return or args.healed_security_return or args.security_red_unlock or args.bridge_entry) and (args.frames != 20000 or args.aim_cycle != 180):
        parser.error("leaving the booth requires --frames 20000 --aim-cycle 180")
    write_route(args.output, args.frames, args.aim_cycle, args.leave_booth, args.leave_airlock, args.enter_parking, args.shop_purchase, args.enter_akropolis, args.enter_tower, args.enter_square, args.square_telephone, args.square_stairs, args.enter_patio, args.patio_swat, args.east_hall_key, args.leave_east_hall, args.enter_cafeteria, args.cafeteria_combat, args.cafeteria_follow_up, args.return_after_cafeteria, args.mist_report, args.enter_hallway, args.enter_fountain, args.fountain_path, args.fountain_protein, args.enter_security_room, args.security_rupert_monitor, args.hallway_blue_key, args.security_blue_unlock, args.enter_forked_road, args.enter_observatory, args.equip_tonfa, args.observatory_combat, args.enter_promenade, args.promenade_combat, args.enter_sanctuary, args.enter_roof_garden, args.sanctuary_red_key, args.roof_garden_pyrokinesis, args.roof_garden_combat, args.roof_garden_bomb, args.roof_garden_healing, args.healed_observatory_return, args.healed_security_return, args.security_red_unlock, args.bridge_entry)


if __name__ == "__main__":
    main()
