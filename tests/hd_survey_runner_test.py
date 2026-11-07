"""Exercise launcher argument forwarding and attribution of a complete survey."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

SURVEY = Path(__file__).resolve().parents[1] / 'tools/hd/survey.py'
RUNNER = r'''
import json, os, sys
from pathlib import Path
binary = Path(sys.argv[1])
assert binary.read_bytes().startswith(b'fixture')
out = Path(os.environ['PE2_SURVEY_OUTPUT'])
location = list(map(int, os.environ['PE2_START_LOCATION'].split(',')))
key = os.environ['PE2_SURVEY_TARGET'].split(':')[1]
report = dict(format='pe2-static-view-survey-v3', matched_frames=30,
              key=key, location=location, width=320, height=240, buffer_y=0,
              launcher_arguments=sys.argv[1:])
(out/'report.json').write_text(json.dumps(report))
(out/'gpu-state.json').write_text(json.dumps(dict(
    format='pe2-gpu-state-audit-v1', complete=True, key=key,
    location=location, buffer_y=0)))
(out/'vram.bin').write_bytes(bytes(1024*512*2))
(out/'frame.ppm').write_bytes(b'P6\n320 240\n255\n' + bytes([1,2,3])*(320*240))
mutation = os.environ.get('SURVEY_FIXTURE_MUTATE')
if mutation:
    paths = dict(binary=binary, runner=Path(__file__),
                 catalog=Path(os.environ['SURVEY_FIXTURE_CATALOG']),
                 replay=Path(os.environ['PE2_PAD_REPLAY']),
                 replay_source=Path(os.environ.get('SURVEY_FIXTURE_REPLAY', 'unused')))
    with paths[mutation].open('ab') as stream:
        stream.write(b'\n# changed\n' if mutation == 'runner' else b'\n')
'''


@unittest.skipUnless(os.name == 'posix', 'Executable fixture launcher uses a POSIX shebang')
class SurveyRunnerTest(unittest.TestCase):
    def run_survey(self, root, mutation=None, supplied_replay=False):
        binary = root/'binary with spaces'
        binary.write_bytes(b'fixture, deliberately not executable')
        runner = root/'launcher with spaces'
        runner.write_text('#!' + sys.executable + '\n' + RUNNER)
        runner.chmod(0o755)
        catalog = root/'catalog.json'
        catalog.write_text(json.dumps(dict(records=[dict(
            eligible_for_start_test=True, location=[1,2,3,1,1,1],
            keys=['0123456789abcdef'], room='fixture')])))
        disc = root/'disc.cue'
        disc.write_bytes(b'fixture')
        output = root/'output'
        env = dict(os.environ, SURVEY_FIXTURE_CATALOG=str(catalog))
        env.pop('SURVEY_FIXTURE_MUTATE', None)
        if mutation:
            env['SURVEY_FIXTURE_MUTATE'] = mutation
        extra=[]
        if supplied_replay:
            source=root/'custom route.pad';source.write_bytes(b'PE2PAD 1\n0 0041ffff\n')
            env['SURVEY_FIXTURE_REPLAY']=str(source)
            extra=['--replay',str(source)]
        result = subprocess.run([
            sys.executable, str(SURVEY), '--binary', str(binary),
            '--runner', str(runner), '--catalog', str(catalog),
            '--disc', str(disc), '--disc2', str(disc), '--gpu-state',
            '--jobs', '1', '--output', str(output), *extra],
            env=env, capture_output=True, text=True, timeout=30)
        return result, output, dict(binary=binary, runner=runner, catalog=catalog)

    def test_launcher_receives_binary_and_report_hashes_real_inputs(self):
        with tempfile.TemporaryDirectory() as name:
            result, output, paths = self.run_survey(Path(name))
            self.assertEqual(result.returncode, 0, result.stderr)
            report = json.loads((output/'report.json').read_text())
            self.assertTrue(report['selected_complete'])
            self.assertEqual(report['parity_verified'], 1)
            for kind, path in {**paths, 'replay': output/'startup.pad'}.items():
                self.assertEqual(report[kind+'_sha256'], hashlib.sha256(path.read_bytes()).hexdigest())
            for run in report['cases'][0]['runs']:
                args = run['report']['launcher_arguments']
                self.assertEqual(args[0], str(paths['binary'].resolve()))
                self.assertEqual(args[-2:], ['--widescreen', str(run['widescreen'])])

    def test_changed_inputs_cannot_publish_a_complete_report(self):
        for kind in ['binary', 'runner', 'catalog', 'replay']:
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as name:
                result, output, _ = self.run_survey(Path(name), kind)
                self.assertNotEqual(result.returncode, 0)
                self.assertIn(kind.capitalize()+' changed during survey', result.stderr)
                self.assertFalse((output/'report.json').exists())

    def test_supplied_controller_trace_is_copied_and_attributed(self):
        with tempfile.TemporaryDirectory() as name:
            root=Path(name)
            result, output, _=self.run_survey(root,supplied_replay=True)
            self.assertEqual(result.returncode,0,result.stderr)
            report=json.loads((output/'report.json').read_text())
            self.assertEqual((output/'startup.pad').read_bytes(),(root/'custom route.pad').read_bytes())
            self.assertEqual(report['replay_source_sha256'],report['replay_sha256'])
            self.assertEqual(report['scope']['replay'],'provided')

    def test_changed_supplied_trace_cannot_publish_complete_report(self):
        with tempfile.TemporaryDirectory() as name:
            result, output, _=self.run_survey(Path(name),'replay_source',supplied_replay=True)
            self.assertNotEqual(result.returncode,0)
            self.assertIn('Replay source changed during survey',result.stderr)
            self.assertFalse((output/'report.json').exists())


if __name__ == '__main__':
    unittest.main()
